#include "FileSystem.h"

#include <stdio.h>
#include <string.h>
#include <dayos.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	FileSystem rootfs;

	rootfs.addNode("/", new FSDir("dayos", VFS_MODE_RW));
	rootfs.addNode("/", new FSDir("drives", VFS_MODE_RW));
	rootfs.addNode("/dayos", new FSDir("dev", VFS_MODE_RW));

	if (register_service("vfs") != SIGNAL_OK)
	{
		debug_printf("[ VFS ] Could not register VFS service. Will terminate.\n");
		return -1;
	}
	
	pid_t vfs_pid = get_service_pid("vfs");

	message_t msg;
	struct vfs_request* request = (struct vfs_request*)&msg.message;
	while (1)
	{
		while (receive_message(&msg, MESSAGE_ANY) != MESSAGE_RECEIVED)
			sleep(10);

		switch (msg.signal)
		{
			case VFS_SIGNAL_CREATE_DEVICE:

				if (!rootfs.mkdev(request->path, (VFS_OPEN_MODES)request->mode,
								  (DEVICE_TYPES)request->param, msg.sender))
					msg.signal = SIGNAL_FAIL;
				else
					msg.signal = SIGNAL_OK;

				send_message(&msg, msg.sender);
				break;

			case VFS_SIGNAL_MOUNT_DEVICE:
			{
				struct vfs_request req = *request;
				if (receive_message_timeout(&msg, msg.sender, 100, 10) !=
					MESSAGE_RECEIVED)
					break;

				if (!rootfs.mount(req.path, request->path,
						(VFS_OPEN_MODES)req.mode, request->param))
					msg.signal = SIGNAL_FAIL;
				else
					msg.signal = SIGNAL_OK;

				send_message(&msg, msg.sender);
			}
			break;

			case VFS_SIGNAL_MOUNT_RAMDISK:
			{
				if (!rootfs.mount(request->path, (VFS_OPEN_MODES)request->mode,
								  msg.sender))
					msg.signal = SIGNAL_FAIL;
				else
					msg.signal = SIGNAL_OK;

				send_message(&msg, msg.sender);
			}
			break;

			case VFS_SIGNAL_OPEN:
			{
				pid_t sender = msg.sender;
				FSNode* node = rootfs.findNode(request->path);
				struct vfs_file* file = (struct vfs_file*)&msg.message;

				if (!node)
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}

				msg.signal = SIGNAL_OK;
				switch (node->getType())
				{
					case NODE_DEVICE:
					{
						FSDevice* dev = static_cast<FSDevice*>(node);
						file->device = dev->getDriverPID();
						file->type = dev->getDeviceType();
						file->uid = dev->getUID();
						file->guid = dev->getGUID();

						strcpy(file->path, request->path);
					}
					break;

					case NODE_MOUNT:
					{
						FSMount* mount = static_cast<FSMount*>(node);
						file->device = mount->getFilesystemDriver();
						file->type = VFS_MOUNTPOINT;

						// FIXME: Fetch from FS driver!
						file->uid = mount->getUID();
						file->guid = mount->getGUID();

						std::string path;
						path = request->path;
						path = path.substr(strlen(mount->getPath()));
						strcpy(file->path, path.c_str());
					}
					break;

					default:
						msg.signal = SIGNAL_FAIL;
				}

				send_message(&msg, sender);
			}

		    case VFS_SIGNAL_OPEN_DIR: {
				pid_t sender = msg.sender;
				FSNode* node = rootfs.findNode(request->path);
				struct vfs_file* file = (struct vfs_file*) &msg.message;

				if (!node || (node->getType() != NODE_MOUNT 
							  && node->getType() != NODE_DIR))
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}
				
				msg.signal = SIGNAL_OK;
				switch (node->getType())
				{
					case NODE_DIR:
					{
						FSDir* dir = static_cast<FSDir*>(node);
						file->type = VFS_DIRECTORY;
						file->uid = dir->getUID();
						file->guid = dir->getGUID();
						file->nid = dir->getNodeId();
						file->device = vfs_pid;
						file->offset = 0;
						strcpy(file->path, request->path);	
					}
					break;

					case NODE_MOUNT:
					{
						FSMount* mount = static_cast<FSMount*>(node);
						file->device = mount->getFilesystemDriver();
						file->type = VFS_MOUNTPOINT;

						// FIXME: Fetch from FS driver!
						file->uid = mount->getUID();
						file->guid = mount->getGUID();

						std::string path;
						path = request->path;
						path = path.substr(strlen(mount->getPath()));
						
						if(path.empty())
							path = "/";
						
						strcpy(file->path, path.c_str());
					}
					break;
				}
			
				send_message(&msg, sender);
			}
			break;

			 case VFS_SIGNAL_READ_DIR: {
				pid_t sender = msg.sender;
				FSNode* node = rootfs.findNode(request->path);
				struct vfs_file* file = (struct vfs_file*) &msg.message;

				if (!node || (node->getType() != NODE_MOUNT 
							  && node->getType() != NODE_DIR))
				{
					msg.signal = SIGNAL_FAIL;
					send_message(&msg, msg.sender);
					break;
				}

				msg.signal = SIGNAL_OK;
				switch (node->getType())
				{
					case NODE_DIR:
					{
						FSDir* dir = static_cast<FSDir*>(node);
						node = dir->getChild(request->param);
						
						if(!node)
						{
							msg.signal = SIGNAL_FAIL;
							break;
						}
						
						file->type = node->getType();
						file->uid = node->getUID();
						file->guid = node->getGUID();
						file->nid = node->getNodeId();

						strcpy(file->path, node->getName());
					}
					break;

					case NODE_MOUNT:
					{
						FSMount* mount = static_cast<FSMount*>(node);
						file->device = mount->getFilesystemDriver();
						file->type = VFS_MOUNTPOINT;

						// FIXME: Fetch from FS driver!
						file->uid = mount->getUID();
						file->guid = mount->getGUID();
						file->nid = node->getNodeId();

						std::string path;
						path = request->path;
						path = path.substr(strlen(mount->getPath()));
						
						strcpy(file->path, path.c_str());
					}
					break;
				}
			
				send_message(&msg, sender);
			}
			
			default:
			{
				// debug_printf("[ VFS ] Unknown signal %d from %d\n", msg.signal, msg.sender);
			}
		}
	}

	for (;;);
}

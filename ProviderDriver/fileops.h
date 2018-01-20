struct file_operations fops =
{
open:openDev,
release:releaseDev,
write:writeDev,
read:readDev
};

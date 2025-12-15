src_name = "../x64/Release/GsDriver.sys"
dest_name = "driver_data.h"

src_file = open(src_name, "rb")
dest_file = open(dest_name, "w")

src_buf = src_file.read()
dest_file.write("static unsigned char driver_data[] =\n{\n")

init = False
for i, byte in enumerate(src_buf):
    if i % 16 == 0:
        if init:
            dest_file.write(",")
            dest_file.write("\n")
        else:
            init = True
        dest_file.write("0x" + hex(byte)[2:].zfill(2))
    else:
        dest_file.write(", 0x" + hex(byte)[2:].zfill(2))

dest_file.writelines("\n};")
src_file.close()
dest_file.close()

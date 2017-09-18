#!/bin/bash
#
# This script downloads the STM32Cube SDK F4 MCUs
# and validates the downloaded ZIP using MD5 checksums
#
# http://www.st.com/en/embedded-software/stm32cubef4.html
#

agent="STM32CubeMX/4.x"

#
# download $1=url $2=checksum $3=path to extract
#
function download {
	filename=$(echo -n "${1##*/}")
	md5sum=$(md5sum $filename | cut -d " " -f 1)
	if [ ! -e $filename ] || [ $md5sum != $2 ]; then
		wget -c --user-agent="$agent" "$url"
	else
		echo "The SDK has already been downloaded (archive checksum is correct)."
	fi

	echo "Unzipping SDK ..."
	unzip -o $filename $3
	echo "Done."
}

url="http://www.st.com/resource/en/firmware2/stm32cube_fw_f4_v1160.zip"
checksum="e46348d9e11fe01a8b3a3cec02c25441"
download $url $checksum STM32Cube_FW_F4_V1.16.0/Drivers/*

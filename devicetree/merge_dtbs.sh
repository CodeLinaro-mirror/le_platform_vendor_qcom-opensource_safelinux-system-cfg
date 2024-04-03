#!/bin/bash
#SPDX-License-Identifier: GPL-2.0-only
#Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.

usage ()
{
	echo "Err: $1"
	echo "$0 <base DTB dir> <out of tree DTBO dir> <out out dir> <kernel dir>"
}

if [ $# -ne 3 ]
then
	usage "Invalid parameters"
	exit 1
fi

# This regex in file name is supposed to differentiate b/w pcie_ep DTBs and regular ones
PCIE_EP_DTBO_REGEX="pcie_ep"
ARCH="${ARCH:=arm64}"
KDIR=$1
DTBO_DIR=$2
OUT_DIR=$3

match_dtb_to_dtbo()
{
	dtb=$1
	dtbo=$2

	dtbo_compatible=$(cat $dtbo | grep compatible | head -1 | sed -e 's/compatible =//' -e 's/\"//g' -e 's/[;\,]//g')
	dtbo_model=$(cat $dtbo | grep model | head -1 | sed -e 's/model =//' -e 's/\"//g' -e 's/[;\,]//g')


	dtb_compatible=$(cat $dtb | grep compatible | head -1 | sed -e 's/compatible =//' -e 's/\"//g' -e 's/[;\,]//g')
	dtb_model=$(cat $dtb | grep model | head -1 | sed -e 's/model =//' -e 's/\"//g' -e 's/[;\,]//g')

	if [ "$dtb_model" = "$dtbo_model" ]
	then
		return 0
	fi

	for dtb in $dtb_compatible
	do
	for dtbo in $dtbo_compatible
		do
			if [ "$dtb" = "$dtbo" ]
			then
				return 0
			fi
		done
	done
	return 1
}

merge_dtbos()
{
	base_dtb=$1
	base_dts_name=$(echo "$base_dtb" | sed -e 's/\.[^.]*$//')
	base_dts="${base_dts_name}.dts"
	dtbo_files=$2
	matched_dtbos=""

	# Proceed only if the expected DTS file is present
	if [ ! -f $base_dts ]
	then
		return
	fi
	for dtbo_file in $dtbo_files
	do
		dtbs_file=$(echo "$dtbo_file" | sed -e 's/\.[^.]*$//')
		dtbs_file="${dtbs_file}.dts"
		if match_dtb_to_dtbo $base_dts $dtbs_file
		then
			matched_dtbos="${matched_dtbos} ${dtbo_file}"
		fi
	done

	base_name=$(basename $base_dtb)
	base_dts_name=$(echo "$base_name" | sed -e 's/\.[^.]*$//')
	#out_file="${base_dts_name}.dtb.overlay"
	# Since base DTB is same, choose a different name if its a pcie_ep usecase, avoid overwriting

	if echo $dtbo_files | grep -q ${PCIE_EP_DTBO_REGEX}; then
		out_file="${base_dts_name}_${PCIE_EP_DTBO_REGEX}.dtb.overlay"
	else
		out_file="${base_dts_name}.dtb.overlay"
	fi

	if [ "$matched_dtbos" != ""  ]
	then
		# execute the command in verbose mode(-v)
		${KDIR}/scripts/dtc/fdtoverlay -i $base_dtb -o ${OUT_DIR}/${out_file} -v $matched_dtbos
		#exit in case of failure
		if [ $? -ne 0 ]; then
			exit 1
		fi
	fi
}

main()
{
	#build with support of overlay
	make -C ${KDIR} ARCH=${ARCH} DTC_FLAGS="-@" -s qcom/*.dtb

	#refresh the dtb list
	dtb_files=$(find ${KDIR}/arch/arm64/boot/dts/qcom -name "*.dtb")
#	dtbo_files=$(find $DTBO_DIR -name "*.dtbo")
	dtbo_files_regular=$(find $DTBO_DIR -name "*.dtbo" | grep -v "${PCIE_EP_DTBO_REGEX}")
	dtbo_files_pcie_ep=$(find $DTBO_DIR -name "*.dtbo" | grep "${PCIE_EP_DTBO_REGEX}")

	for file in $dtb_files
	do
		#merge_dtbos $file "${dtbo_files[@]}"
		# For same Base DTB we can have a pcie_ep and regular DTBO
		# # At the same time, we can have more than 1 overlay of each type (pcie_ep or regular ones)
		# Hence segregate, and generate 2 types of DTBs, if match happens
		merge_dtbos $file "${dtbo_files_regular[@]}"
		merge_dtbos $file "${dtbo_files_pcie_ep[@]}"
	done
}

main

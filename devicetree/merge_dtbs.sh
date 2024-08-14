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

ARCH="${ARCH:=arm64}"
KDIR=$1
DTBO_DIR=$2
OUT_DIR=$3

match_dtb_to_dtbo()
{
	dtb=$1
	dtbo=$2

	dtbo_compatible=$(fdtget -t s "$dtbo" / "compatible" | sed -e 's/\"//g' -e 's/[;\,]//g')
	dtbo_model=$(fdtget -t s "$dtbo" / "model" | sed -e 's/\"//g' -e 's/[;\,]//g')

	dtb_compatible=$(fdtget -t s "$dtb" / "compatible" | sed -e 's/\"//g' -e 's/[;\,]//g')
	dtb_model=$(fdtget -t s "$dtb" / "model" | sed -e 's/\"//g' -e 's/[;\,]//g')

	if [ "$dtb_model" = "$dtbo_model" ]; then
		return 0
	fi

	for dtb in $dtb_compatible; do
		for dtbo in $dtbo_compatible; do
			if [ "$dtb" = "$dtbo" ]; then
				return 0
			fi
		done
	done
	return 1
}

merge_dtbos()
{
	base_dtb=$1
	dtbo_files=$2
	matched_dtbos=""

	for dtbo_file in $dtbo_files
	do
		if match_dtb_to_dtbo "$base_dtb" "$dtbo_file"
		then
			matched_dtbos="${matched_dtbos} ${dtbo_file}"
		fi
	done

	matched_dtbos=$(echo "$matched_dtbos" | xargs)
	IFS=' ' read -ra matched_dtbos_list <<< "$matched_dtbos"
	base_name=$(basename "$base_dtb")
	base_dts_name="${base_name//.dtb/}"
	out_file="${base_dts_name}.dtb.overlay"

	if [ "$matched_dtbos" != "" ]
	then
		# execute the command in verbose mode(-v)
		if ! "${KDIR}"/scripts/dtc/fdtoverlay -i "$base_dtb" -o \
			"${OUT_DIR}"/"${out_file}" -v "${matched_dtbos_list[@]}"; then
                        exit 1
		fi
	fi
}

main()
{
	#build with support of overlay
	make -C "${KDIR}" ARCH=${ARCH} DTC_FLAGS="-@" -s qcom/*.dtb

	#refresh the dtb list
	dtb_files=$(find "${KDIR}"/arch/arm64/boot/dts/qcom -name "*.dtb")
	dtbo_files=$(find "$DTBO_DIR" -name "*.dtbo")

	for file in $dtb_files
	do
		merge_dtbos "$file" "${dtbo_files[@]}"
	done
}

main

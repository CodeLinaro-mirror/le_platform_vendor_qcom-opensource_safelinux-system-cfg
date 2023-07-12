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

KDIR=$1
DTBO_DIR=$2
OUT_DIR=$3

dtb_files=$(find ${KDIR}/arch/arm64/boot/dts/qcom -name "*.dtb")

dtbo_files=$(find $DTBO_DIR -name "*.dtbo")


#dtbo_files=$(find ${KDIR}/arch/arm64/boot/dts/qcom -name "*.dtbo")

create_dts()
{
        base_dts=$1
        base_dtb=$2

        ${KDIR}/scripts/dtc/dtc -I dtb -O dts -o $base_dts $base_dtb

}

#create dts from dtbs
: <<'END_COMMENT'
for base_dtb in $dtb_files
do
	base_dts=$(echo "$base_dtb" | sed -e 's/\.[^.]*$//')
        base_dts="${base_dts}.dts"
        #echo $file : create dts
	create_dts $base_dts $base_dtb
done
END_COMMENT

#build with support of overlay
make -C ${KDIR} DTC_FLAGS="-@" -s  qcom/*.dtb

#refresh the dtb list
dtb_files=$(find ${KDIR}/arch/arm64/boot/dts/qcom -name "*.dtb")

match_dtb_to_dtbo()
{
	dtb=$1
	dtbo=$2
	ret=1

	dtbo_compatible=$(cat $dtbo | grep compatible | head -1 | sed -e 's/compatible =//' -e 's/\"//g' -e 's/[;\,]//g')
	dtbo_model=$(cat $dtbo | grep model | head -1 | sed -e 's/model =//' -e 's/\"//g' -e 's/[;\,]//g')


	dtb_compatible=$(cat $dtb | grep compatible | head -1 | sed -e 's/compatible =//' -e 's/\"//g' -e 's/[;\,]//g')
	dtb_model=$(cat $dtb | grep model | head -1 | sed -e 's/model =//' -e 's/\"//g' -e 's/[;\,]//g')

	if [ "$dtb_model" = "$dtbo_model" ]
	then
		ret=0
		#echo model matched
		return "$ret"
	fi

	for dtb in $dtb_compatible
	do
	for dtbo in $dtbo_compatible
		do
		#echo compare 1: $dtb with $dtbo
			if [ "$dtb" = "$dtbo" ]
			then
				ret=0
				#echo "1: match for $dtb with $dtbo"
				return "$ret"
			fi
		done
	done
	return "$ret"
}


merge_dtbos()
{
	base_dtb=$1
	base_dts_name=$(echo "$base_dtb" | sed -e 's/\.[^.]*$//')
	base_dts="${base_dts_name}.dts"
	dtbo_files=$2

	matched_dtbos=""

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
	out_file="${base_dts_name}.overlay.dtb"


	if [ "$matched_dtbos" != ""  ]
	then
		echo "=============================================================="
		echo dtbos matches : $matched_dtbos
		echo base dtb: $base_dtb
		echo output file: ${OUT_DIR}/${out_file}
		echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		${KDIR}/scripts/dtc/fdtoverlay -i $base_dtb -o ${OUT_DIR}/${out_file} -v $matched_dtbos
	fi
}

for file in $dtb_files
do
	#echo $file
	merge_dtbos $file $dtbo_files
done

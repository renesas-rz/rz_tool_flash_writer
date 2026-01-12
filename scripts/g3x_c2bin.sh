#! /bin/bash
#
# Sample script to generate a DDR parameter binary file for RZ/G3S from a DDR parameter source file.
#

################################################################################
# Set bash parameters
set -uae
set -o pipefail
################################################################################
# Set parameters
DDR_PARAM_IN=${1}
################################################################################
DDR_PARAM_COMPRESS=ddr_param_compress.c
DDR_PARAM_VARIABLE=ddr_param_variable.c
DDR_PARAM_SED=ddr_param.sed

filename=$(basename "$DDR_PARAM_IN")
rm -f "${filename%.c}.bin"
DDR_PARAM_BINARY="${filename%.c}.bin"
################################################################################
# Find all #define lines in input *.c, create sed rule
MATCHES=$(grep -E "^#define[[:space:]]+[0-9A-Za-z]+[[:space:]]+0x[0-9A-Fa-f]+" "$DDR_PARAM_IN" || true)
if [[ -n "$MATCHES" ]]; then
    echo "$MATCHES" | while read -r LINE; do
        NAME=$(echo "$LINE" | awk '{print $2}')
        VALUE=$(echo "$LINE" | awk '{print $3}')
        echo "s|$NAME|$VALUE|g" >> "${DDR_PARAM_SED}"
    done
else
    > "${DDR_PARAM_SED}"
fi
################################################################################
# Compress parameters
rm -f ${DDR_PARAM_COMPRESS}

cat ${DDR_PARAM_IN} |
    awk 'NF' |
    tr -d '\n' |
    tr -d '\t' |
    sed -E 's|const|\nconst|g' |
    grep -E '^const' |
    tee -a ${DDR_PARAM_COMPRESS}
################################################################################
# Replace address
cat ${DDR_PARAM_COMPRESS} |
    sed -E -f ${DDR_PARAM_SED} |
    tee ${DDR_PARAM_COMPRESS}.tmp
################################################################################
cp -uv ${DDR_PARAM_COMPRESS}.tmp ${DDR_PARAM_COMPRESS}
################################################################################
# Pick variable
rm -f ${DDR_PARAM_VARIABLE}
################################################################################
ddr_version_str_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -F 'ddr_version_str' |
    grep -oE '"[^"]+"' |
    sed -E 's|.(.+).|\1|' |
    tr -d '\n' |
    xxd -p |
    awk '{ 
        hex = $0;
        while (length(hex) < 16) hex = hex "00";     # pad to full 8 bytes (16 hex characters)
        print substr(hex, 1, 8);
        print substr(hex, 9, 8);
    }' |
    awk '{ printf("0x%s\n", $0); }' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_setup_mc_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_setup_mc' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0123456789abcdef]{1,8}' |
    awk '{
        h = substr($0, 3);
        pad = sprintf("%08s", h);
        gsub(/ /, "0", pad);
        printf("0x%s%s%s%s\n", substr(pad, 7, 2), substr(pad, 5, 2), substr(pad, 3, 2), substr(pad, 1, 2));
    }' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_c_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_c' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0123456789abcdef]{1,8}' |
    awk '{
        h = substr($0, 3);
        pad = sprintf("%08s", h);
        gsub(/ /, "0", pad);
        printf("0x%s%s%s%s\n", substr(pad, 7, 2), substr(pad, 5, 2), substr(pad, 3, 2), substr(pad, 1, 2));
    }' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_1d_dat1_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_1d_dat1' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk 'END { print NR }')

param_phyinit_1d_dat1_size_align_8bytes=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_1d_dat1' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk '
    BEGIN {
        count = 0;
    }
    {
        h = substr($0, 3);
        pad = sprintf("%04s", h);
        gsub(/ /, "0", pad);
        byte1 = substr(pad, 3, 2);
        byte2 = substr(pad, 1, 2);
        printf("0x%s\n", byte1);
        printf("0x%s\n", byte2);
        count += 2;
    }
    END {
        pad_needed = (8 - (count % 8)) % 8;
        for (i = 0; i < pad_needed; i++) {
            printf("0x00\n");
        }
    }
    ' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_2d_dat1_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_2d_dat1' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk 'END { print NR }')

param_phyinit_2d_dat1_size_align_8bytes=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_2d_dat1' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk '
    BEGIN {
        count = 0;
    }
    {
        h = substr($0, 3);
        pad = sprintf("%04s", h);
        gsub(/ /, "0", pad);
        byte1 = substr(pad, 3, 2);
        byte2 = substr(pad, 1, 2);
        printf("0x%s\n", byte1);
        printf("0x%s\n", byte2);
        count += 2;
    }
    END {
        pad_needed = (8 - (count % 8)) % 8;
        for (i = 0; i < pad_needed; i++) {
            printf("0x00\n");
        }
    }
    ' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_i_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_i' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0123456789abcdef]{1,8}' |
    awk '{
        h = substr($0, 3);
        pad = sprintf("%08s", h);
        gsub(/ /, "0", pad);
        printf("0x%s%s%s%s\n", substr(pad, 7, 2), substr(pad, 5, 2), substr(pad, 3, 2), substr(pad, 1, 2));
    }' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_1d_dat0_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_1d_dat0' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk 'END { print NR }')

param_phyinit_1d_dat0_size_align_8bytes=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_1d_dat0' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk '
    BEGIN {
        count = 0;
    }
    {
        h = substr($0, 3);
        pad = sprintf("%04s", h);
        gsub(/ /, "0", pad);
        byte1 = substr(pad, 3, 2);
        byte2 = substr(pad, 1, 2);
        printf("0x%s\n", byte1);
        printf("0x%s\n", byte2);
        count += 2;
    }
    END {
        pad_needed = (8 - (count % 8)) % 8;
        for (i = 0; i < pad_needed; i++) {
            printf("0x00\n");
        }
    }
    ' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_2d_dat0_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_2d_dat0' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk 'END { print NR }')

param_phyinit_2d_dat0_size_align_8bytes=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_2d_dat0' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0-9a-f]{1,4}' |
    awk '
    BEGIN {
        count = 0;
    }
    {
        h = substr($0, 3);
        pad = sprintf("%04s", h);
        gsub(/ /, "0", pad);
        byte1 = substr(pad, 3, 2);
        byte2 = substr(pad, 1, 2);
        printf("0x%s\n", byte1);
        printf("0x%s\n", byte2);
        count += 2;
    }
    END {
        pad_needed = (8 - (count % 8)) % 8;
        for (i = 0; i < pad_needed; i++) {
            printf("0x00\n");
        }
    }
    ' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
param_phyinit_swizzle_size=$(cat ${DDR_PARAM_COMPRESS} |
    grep -E 'param_phyinit_swizzle' |
    awk '{print tolower($0)}' |
    grep -oE '0x[0123456789abcdef]{1,8}' |
    awk '{
        h = substr($0, 3);
        pad = sprintf("%08s", h);
        gsub(/ /, "0", pad);
        printf("0x%s%s%s%s\n", substr(pad, 7, 2), substr(pad, 5, 2), substr(pad, 3, 2), substr(pad, 1, 2));
    }' |
    tee -a ${DDR_PARAM_VARIABLE} |
    awk 'END { print NR/2 }')
################################################################################
echo -e "\r\n=========Arrays Size=========================="
echo -e "param_setup_mc_size: \t\t${param_setup_mc_size} elements"
echo -e "param_phyinit_c_size: \t\t${param_phyinit_c_size} elements"
echo -e "param_phyinit_1d_dat1_size: \t${param_phyinit_1d_dat1_size} elements"
echo -e "param_phyinit_2d_dat1_size: \t${param_phyinit_2d_dat1_size} elements"
echo -e "param_phyinit_i_size: \t\t${param_phyinit_i_size} elements"
echo -e "param_phyinit_1d_dat0_size: \t${param_phyinit_1d_dat0_size} elements"
echo -e "param_phyinit_2d_dat0_size: \t${param_phyinit_2d_dat0_size} elements"
echo -e "param_phyinit_swizzle_size: \t${param_phyinit_swizzle_size} elements"
################################################################################
echo -e "\r\n========Aligned 8 bytes======================="
temp=$(((param_phyinit_1d_dat1_size_align_8bytes - param_phyinit_1d_dat1_size)*2))
echo -e "param_phyinit_1d_dat1_size: \t+${temp} bytes"
temp=$(((param_phyinit_2d_dat1_size_align_8bytes - param_phyinit_2d_dat1_size)*2))
echo -e "param_phyinit_2d_dat1_size: \t+${temp} bytes"
temp=$(((param_phyinit_1d_dat0_size_align_8bytes - param_phyinit_1d_dat0_size)*2))
echo -e "param_phyinit_1d_dat0_size: \t+${temp} bytes"
temp=$(((param_phyinit_2d_dat0_size_align_8bytes - param_phyinit_2d_dat0_size)*2))
echo -e "param_phyinit_2d_dat0_size: \t+${temp} bytes"
################################################################################
all_size_of_arrays=8
total_size=$((ddr_version_str_size*8 + \
    param_setup_mc_size*8 + \
    param_phyinit_c_size*8 + \
    param_phyinit_1d_dat1_size_align_8bytes*2 + \
    param_phyinit_2d_dat1_size_align_8bytes*2 + \
    param_phyinit_i_size*8 + \
    param_phyinit_1d_dat0_size_align_8bytes*2 +\
    param_phyinit_2d_dat0_size_align_8bytes*2 + \
    param_phyinit_swizzle_size*8 + \
    all_size_of_arrays*4))
echo -e "\r\n=============================================="
echo -e "Total size of binary file: \t${total_size} bytes"
################################################################################
# Convert binary file
xxd -r -p ${DDR_PARAM_VARIABLE} ${DDR_PARAM_BINARY}
################################################################################
# Append the size of the array to the end of the binary file
append_uint32_le() {
    local val=$1
    printf "%08x" "$val" | sed 's/\(..\)/\1\n/g' | tac | tr -d '\n' | xxd -r -p
}
################################################################################
append_uint32_le "$param_setup_mc_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_c_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_1d_dat1_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_2d_dat1_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_i_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_1d_dat0_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_2d_dat0_size" >> ${DDR_PARAM_BINARY}
append_uint32_le "$param_phyinit_swizzle_size" >> ${DDR_PARAM_BINARY}
################################################################################
# Clear temporary files
rm -f *.tmp
rm -f *.sed
rm -f ${DDR_PARAM_COMPRESS}
rm -f ${DDR_PARAM_VARIABLE}
################################################################################

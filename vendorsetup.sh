# nuke
rm -rf device/realme/RM6785
rm -rf vendor/realme
rm -rf kernel/realme/mt6785
rm -rf realme/realme-firmwar
rm -rf device/mediatek/sepolicy

# clone
git clone https://github.com/iamthecloverly/android_device_realme_RM6785 -b Elixir_3.0 device/realme/RM6785
git clone https://github.com/realme-mt6785-devs/proprietary_vendor_realme.git vendor/realme
git clone https://github.com/realme-mt6785-devs/android_kernel_realme_mt6785.git kernel/realme/mt6785
git clone https://github.com/realme-mt6785-devs/proprietary_vendor_realme-firmware realme/realme-firmware
git clone https://github.com/realme-mt6785-devs/android_device_mediatek_sepolicy.git device/mediatek/sepolicy

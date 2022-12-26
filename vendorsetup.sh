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
git clone https://github.com/realme-mt6785-devs/android_device_realme_RM6785-kernel.git device/realme/RM6785-kernel
git clone https://github.com/realme-mt6785-devs/vendor_mediatek_opensource_interfaces.git vendor/mediatek/opensource/interfaces

cd external/faceunlock && wget https://pastebin.com/raw/EbesA2Wm && patch -p1  < EbesA2Wm
#patch for brightness slider 
cd frameworks/base && wget https://raw.githubusercontent.com/sarthakroy2002/random-stuff/main/Patches/Fix-brightness-slider-curve-for-some-devices-a12l.patch
patch -p1 < *.patch && cd -

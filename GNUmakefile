.PHONY: all
all: SigmaoOS.iso

.PHONY: all-hdd
all-hdd: SigmaoOS.hdd

.PHONY: run
run: SigmaoOS.iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom SigmaoOS.iso -boot d -monitor stdio

.PHONY: runfs
runfs: SigmaoOS.iso
	qemu-system-x86_64 -M q35 -m 2G -cdrom SigmaoOS.iso -boot d -full-screen

.PHONY: run-uefi
run-uefi: ovmf-x64 SigmaoOS.iso
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -cdrom SigmaoOS.iso -boot d

.PHONY: run-hdd
run-hdd: SigmaoOS.hdd
	qemu-system-x86_64 -M q35 -m 2G -hda SigmaoOS.hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 SigmaoOS.hdd
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -hda SigmaoOS.hdd

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1
	make -C limine

.PHONY: kernel
kernel:
	cd kernel/; bash buildall.sh

SigmaoOS.iso: limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel/kernel.elf assets/*.bmp \
<<<<<<< HEAD
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-eltorito-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-eltorito-efi.bin \
=======
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
>>>>>>> 7e9ca7b (..)
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o SigmaoOS.iso
	limine/limine-s2deploy SigmaoOS.iso
	rm -rf iso_root
	make clean

SigmaoOS.hdd: limine kernel
	rm -f SigmaoOS.hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=SigmaoOS.hdd
	parted -s SigmaoOS.hdd mklabel gpt
	parted -s SigmaoOS.hdd mkpart ESP fat32 2048s 100%
	parted -s SigmaoOS.hdd set 1 esp on
	limine/limine-s2deploy SigmaoOS.hdd
	sudo losetup -Pf --show SigmaoOS.hdd >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v kernel/kernel.elf limine.cfg assets/* limine/limine.sys img_mount/
	sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root SigmaoOS.hdd
	bash clean.sh

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf-x64
	$(MAKE) -C kernel distclean

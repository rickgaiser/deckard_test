all:
	make -C ppc-iop all
	make -C iop all

clean:
	make -C ppc-iop clean
	make -C iop clean

debug:
	make -C ppc-iop debug
	make -C iop debug

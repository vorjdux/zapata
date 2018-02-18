all:
	./.build all

j4:
	./.build j4

clean:
	./.build clean

install:
	./.build install

uninstall:
	./.build uninstall

distcheck:
	./.build distcheck

distclean:
	./.build distclean

config:
	./.build config

debug:
	./.build debug

bump:
	./.repo bump minor

deb:
	sudo rm -rfv upstream/*
	./.build package

ppa:
	sudo rm -rf zapata-*.tar.gz zapata-*_source.changes zapata-*_source.build zapata-*_source.ppa.upload zapata-*.dsc
	./.repo bump minor
	./.build ppa


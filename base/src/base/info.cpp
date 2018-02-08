/*
The MIT License (MIT)

Copyright (c) 2017 n@zgul <n@zgul.me>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <zapata/file/manip.h>

#include <magic.h>
#include <iostream>

namespace zpt {

#define _MIMETYPE_LEN 412
const char* mimetype_names[] = {"x-world/x-3dmf",
				"application/octet-stream",
				"application/x-authorware-bin",
				"application/x-authorware-map",
				"application/x-authorware-seg",
				"text/vnd.abc",
				"text/html",
				"video/animaflex",
				"application/postscript",
				"audio/aiff",
				"audio/x-aiff",
				"application/x-aim",
				"text/x-audiosoft-intra",
				"application/x-navi-animation",
				"application/x-nokia-9000-communicator-add-on-software",
				"application/mime",
				"application/arj",
				"image/x-jg",
				"video/x-ms-asf",
				"text/x-asm",
				"text/asp",
				"application/x-mplayer2",
				"video/x-ms-asf-plugin",
				"audio/basic",
				"audio/x-au",
				"application/x-troff-msvideo",
				"video/avi",
				"video/msvideo",
				"video/x-msvideo",
				"video/avs-video",
				"application/x-bcpio",
				"application/mac-binary",
				"application/macbinary",
				"application/x-binary",
				"application/x-macbinary",
				"image/bmp",
				"image/x-windows-bmp",
				"application/book",
				"application/x-bzip2",
				"application/x-bsh",
				"application/x-bzip",
				"text/plain",
				"text/x-c",
				"application/vnd.ms-pki.seccat",
				"application/clariscad",
				"application/x-cocoa",
				"application/cdf",
				"application/x-cdf",
				"application/x-netcdf",
				"application/pkix-cert",
				"application/x-x509-ca-cert",
				"application/x-chat",
				"application/java",
				"application/java-byte-code",
				"application/x-java-class",
				"application/x-cpio",
				"application/mac-compactpro",
				"application/x-compactpro",
				"application/x-cpt",
				"application/pkcs-crl",
				"application/pkix-crl",
				"application/x-x509-user-cert",
				"application/x-csh",
				"text/x-script.csh",
				"application/x-pointplus",
				"text/css",
				"application/x-director",
				"application/x-deepv",
				"video/x-dv",
				"video/dl",
				"video/x-dl",
				"application/msword",
				"application/commonground",
				"application/drafting",
				"application/x-dvi",
				"drawing/x-dwf",
				"model/vnd.dwf",
				"application/acad",
				"image/vnd.dwg",
				"image/x-dwg",
				"application/dxf",
				"text/x-script.elisp",
				"application/x-bytecode.elisp",
				"application/x-elc",
				"application/x-envoy",
				"application/x-esrehber",
				"text/x-setext",
				"application/envoy",
				"text/x-fortran",
				"application/vnd.fdf",
				"application/fractals",
				"image/fif",
				"video/fli",
				"video/x-fli",
				"image/florian",
				"text/vnd.fmi.flexstor",
				"video/x-atomic3d-feature",
				"image/vnd.fpx",
				"image/vnd.net-fpx",
				"application/freeloader",
				"audio/make",
				"image/g3fax",
				"image/gif",
				"video/gl",
				"video/x-gl",
				"audio/x-gsm",
				"application/x-gsp",
				"application/x-gss",
				"application/x-gtar",
				"application/x-compressed",
				"application/x-gzip",
				"multipart/x-gzip",
				"text/x-h",
				"application/x-hdf",
				"application/x-helpfile",
				"application/vnd.hp-hpgl",
				"text/x-script",
				"application/hlp",
				"application/x-winhelp",
				"application/binhex",
				"application/binhex4",
				"application/mac-binhex",
				"application/mac-binhex40",
				"application/x-binhex40",
				"application/x-mac-binhex40",
				"application/hta",
				"text/x-component",
				"text/webviewhtml",
				"x-conference/x-cooltalk",
				"image/x-icon",
				"image/ief",
				"application/iges",
				"model/iges",
				"application/x-ima",
				"application/x-httpd-imap",
				"application/inf",
				"application/x-internett-signup",
				"application/x-ip2",
				"video/x-isvideo",
				"audio/it",
				"application/x-inventor",
				"i-world/i-vrml",
				"application/x-livescreen",
				"audio/x-jam",
				"text/x-java-source",
				"application/x-java-commerce",
				"image/jpeg",
				"image/pjpeg",
				"image/x-jps",
				"application/x-javascript",
				"image/jutvision",
				"audio/midi",
				"music/x-karaoke",
				"application/x-ksh",
				"text/x-script.ksh",
				"audio/nspaudio",
				"audio/x-nspaudio",
				"audio/x-liveaudio",
				"application/x-latex",
				"application/lha",
				"application/x-lha",
				"application/x-lisp",
				"text/x-script.lisp",
				"text/x-la-asf",
				"application/x-lzh",
				"application/lzx",
				"application/x-lzx",
				"text/x-m",
				"video/mpeg",
				"audio/mpeg",
				"audio/x-mpequrl",
				"application/x-troff-man",
				"application/x-navimap",
				"application/mbedlet",
				"application/x-magic-cap-package-1.0",
				"application/mcad",
				"application/x-mathcad",
				"image/vasa",
				"text/mcf",
				"application/netmc",
				"application/x-troff-me",
				"message/rfc822",
				"application/x-midi",
				"audio/x-mid",
				"audio/x-midi",
				"music/crescendo",
				"x-music/x-midi",
				"application/x-frame",
				"application/x-mif",
				"www/mime",
				"audio/x-vnd.audioexplosion.mjuicemediafile",
				"video/x-motion-jpeg",
				"application/base64",
				"application/x-meme",
				"audio/mod",
				"audio/x-mod",
				"video/quicktime",
				"video/x-sgi-movie",
				"audio/x-mpeg",
				"video/x-mpeg",
				"video/x-mpeq2a",
				"audio/mpeg3",
				"audio/x-mpeg-3",
				"application/x-project",
				"application/vnd.ms-project",
				"application/marc",
				"application/x-troff-ms",
				"application/x-vnd.audioexplosion.mzz",
				"image/naplps",
				"application/vnd.nokia.configuration-message",
				"image/x-niff",
				"application/x-mix-transfer",
				"application/x-conference",
				"application/x-navidoc",
				"application/oda",
				"application/x-omc",
				"application/x-omcdatamaker",
				"application/x-omcregerator",
				"text/x-pascal",
				"application/pkcs10",
				"application/x-pkcs10",
				"application/pkcs-12",
				"application/x-pkcs12",
				"application/x-pkcs7-signature",
				"application/pkcs7-mime",
				"application/x-pkcs7-mime",
				"application/x-pkcs7-certreqresp",
				"application/pkcs7-signature",
				"application/pro_eng",
				"text/pascal",
				"image/x-portable-bitmap",
				"application/vnd.hp-pcl",
				"application/x-pcl",
				"image/x-pict",
				"image/x-pcx",
				"chemical/x-pdb",
				"application/pdf",
				"audio/make.my.funk",
				"image/x-portable-graymap",
				"image/x-portable-greymap",
				"image/pict",
				"application/x-newton-compatible-pkg",
				"application/vnd.ms-pki.pko",
				"text/x-script.perl",
				"application/x-pixclscript",
				"image/x-xpixmap",
				"text/x-script.perl-module",
				"application/x-pagemaker",
				"image/png",
				"application/x-portable-anymap",
				"image/x-portable-anymap",
				"application/mspowerpoint",
				"application/vnd.ms-powerpoint",
				"model/x-pov",
				"image/x-portable-pixmap",
				"application/powerpoint",
				"application/x-mspowerpoint",
				"application/x-freelance",
				"paleovu/x-pv",
				"text/x-script.phyton",
				"applicaiton/x-bytecode.python",
				"audio/vnd.qcelp",
				"image/x-quicktime",
				"video/x-qtc",
				"audio/x-pn-realaudio",
				"audio/x-pn-realaudio-plugin",
				"audio/x-realaudio",
				"application/x-cmu-raster",
				"image/cmu-raster",
				"image/x-cmu-raster",
				"text/x-script.rexx",
				"image/vnd.rn-realflash",
				"image/x-rgb",
				"application/vnd.rn-realmedia",
				"audio/mid",
				"application/ringing-tones",
				"application/vnd.nokia.ringing-tone",
				"application/vnd.rn-realplayer",
				"application/x-troff",
				"image/vnd.rn-realpix",
				"text/richtext",
				"text/vnd.rn-realtext",
				"application/rtf",
				"application/x-rtf",
				"video/vnd.rn-realvideo",
				"audio/s3m",
				"application/x-tbook",
				"application/x-lotusscreencam",
				"text/x-script.guile",
				"text/x-script.scheme",
				"video/x-scm",
				"application/sdp",
				"application/x-sdp",
				"application/sounder",
				"application/sea",
				"application/x-sea",
				"application/set",
				"text/sgml",
				"text/x-sgml",
				"application/x-sh",
				"application/x-shar",
				"text/x-script.sh",
				"text/x-server-parsed-html",
				"audio/x-psid",
				"application/x-sit",
				"application/x-stuffit",
				"application/x-koan",
				"application/x-seelogo",
				"application/smil",
				"audio/x-adpcm",
				"application/solids",
				"application/x-pkcs7-certificates",
				"text/x-speech",
				"application/futuresplash",
				"application/x-sprite",
				"application/x-wais-source",
				"application/streamingmedia",
				"application/vnd.ms-pki.certstore",
				"application/step",
				"application/sla",
				"application/vnd.ms-pki.stl",
				"application/x-navistyle",
				"application/x-sv4cpio",
				"application/x-sv4crc",
				"application/x-world",
				"x-world/x-svr",
				"application/x-shockwave-flash",
				"application/x-tar",
				"application/toolbook",
				"application/x-tcl",
				"text/x-script.tcl",
				"text/x-script.tcsh",
				"application/x-tex",
				"application/x-texinfo",
				"application/plain",
				"application/gnutar",
				"image/tiff",
				"image/x-tiff",
				"audio/tsp-audio",
				"application/dsptype",
				"audio/tsplayer",
				"text/tab-separated-values",
				"text/x-uil",
				"text/uri-list",
				"application/i-deas",
				"application/x-ustar",
				"multipart/x-ustar",
				"text/x-uuencode",
				"application/x-cdlink",
				"text/x-vcalendar",
				"application/vda",
				"video/vdo",
				"application/groupwise",
				"video/vivo",
				"video/vnd.vivo",
				"application/vocaltec-media-desc",
				"application/vocaltec-media-file",
				"audio/voc",
				"audio/x-voc",
				"video/vosaic",
				"audio/voxware",
				"audio/x-twinvq-plugin",
				"audio/x-twinvq",
				"application/x-vrml",
				"model/vrml",
				"x-world/x-vrml",
				"x-world/x-vrt",
				"application/x-visio",
				"application/wordperfect6.0",
				"application/wordperfect6.1",
				"audio/wav",
				"audio/x-wav",
				"application/x-qpro",
				"image/vnd.wap.wbmp",
				"application/vnd.xara",
				"application/x-123",
				"windows/metafile",
				"text/vnd.wap.wml",
				"application/vnd.wap.wmlc",
				"text/vnd.wap.wmlscript",
				"application/vnd.wap.wmlscriptc",
				"application/wordperfect",
				"application/x-wpwin",
				"application/x-lotus",
				"application/mswrite",
				"application/x-wri",
				"text/scriplet",
				"application/x-wintalk",
				"image/x-xbitmap",
				"image/x-xbm",
				"image/xbm",
				"video/x-amt-demorun",
				"xgl/drawing",
				"image/vnd.xiff",
				"application/excel",
				"application/x-excel",
				"application/x-msexcel",
				"application/vnd.ms-excel",
				"audio/xm",
				"application/xml",
				"text/xml",
				"xgl/movie",
				"application/x-vnd.ls-xpix",
				"image/xpm",
				"video/x-amt-showrun",
				"image/x-xwd",
				"image/x-xwindowdump",
				"application/x-compress",
				"application/x-zip-compressed",
				"application/zip",
				"multipart/x-zip",
				"text/x-script.zsh"};

const char* mimetype_extensions[] = {
    ".3dm",  ".a",     ".aab",  ".aam",     ".aas",    ".abc",   ".acgi",  ".afl",  ".ai",    ".aif",   ".aif",
    ".aim",  ".aip",   ".ani",  ".aos",     ".aps",    ".arj",   ".art",   ".asf",  ".asm",   ".asp",   ".asx",
    ".asx",  ".au",    ".au",   ".avi",     ".avi",    ".avi",   ".avi",   ".avs",  ".bcpio", ".bin",   ".bin",
    ".bin",  ".bin",   ".bm",   ".bmp",     ".boo",    ".boz",   ".bsh",   ".bz",   ".txt",   ".c",     ".cat",
    ".ccad", ".cco",   ".cdf",  ".cdf",     ".cdf",    ".cer",   ".cer",   ".cha",  ".class", ".class", ".class",
    ".cpio", ".cpt",   ".cpt",  ".cpt",     ".crl",    ".crl",   ".crt",   ".csh",  ".csh",   ".css",   ".css",
    ".dcr",  ".deepv", ".dif",  ".dl",      ".dl",     ".doc",   ".dp",    ".drw",  ".dvi",   ".dwf",   ".dwf",
    ".dwg",  ".dwg",   ".dwg",  ".dxf",     ".el",     ".elc",   ".elc",   ".env",  ".es",    ".etx",   ".evy",
    ".f",    ".fdf",   ".fif",  ".fif",     ".fli",    ".fli",   ".flo",   ".flx",  ".fmf",   ".fpx",   ".fpx",
    ".frl",  ".funk",  ".g3",   ".gif",     ".gl",     ".gl",    ".gsd",   ".gsp",  ".gss",   ".gtar",  ".gz",
    ".gz",   ".gzip",  ".h",    ".hdf",     ".help",   ".hgl",   ".hlb",   ".hlp",  ".hlp",   ".hqx",   ".hqx",
    ".hqx",  ".hqx",   ".hqx",  ".hqx",     ".hta",    ".htc",   ".htt",   ".ice",  ".ico",   ".ief",   ".iges",
    ".iges", ".ima",   ".imap", ".inf",     ".ins",    ".ip",    ".isu",   ".it",   ".iv",    ".ivr",   ".ivy",
    ".jam",  ".jav",   ".jcm",  ".jfif",    ".jfif",   ".jps",   ".js",    ".jut",  ".kar",   ".kar",   ".ksh",
    ".ksh",  ".la",    ".la",   ".lam",     ".latex",  ".lha",   ".lha",   ".lsp",  ".lsp",   ".lsx",   ".lzh",
    ".lzx",  ".lzx",   ".m",    ".m1v",     ".m2a",    ".m3u",   ".man",   ".map",  ".mbd",   ".mc$",   ".mcd",
    ".mcd",  ".mcf",   ".mcf",  ".mcp",     ".me",     ".mht",   ".mid",   ".mid",  ".mid",   ".mid",   ".mid",
    ".mif",  ".mif",   ".mime", ".mjf",     ".mjpg",   ".mm",    ".mm",    ".mod",  ".mod",   ".moov",  ".movie",
    ".mp2",  ".mp2",   ".mp2",  ".mp3",     ".mp3",    ".mpc",   ".mpp",   ".mrc",  ".ms",    ".mzz",   ".nap",
    ".ncm",  ".nif",   ".nix",  ".nsc",     ".nvd",    ".oda",   ".omc",   ".omcd", ".omcr",  ".p",     ".p10",
    ".p10",  ".p12",   ".p12",  ".p7a",     ".p7c",    ".p7c",   ".p7r",   ".p7s",  ".part",  ".pas",   ".pbm",
    ".pcl",  ".pcl",   ".pct",  ".pcx",     ".pdb",    ".pdf",   ".pfunk", ".pgm",  ".pgm",   ".pic",   ".pkg",
    ".pko",  ".pl",    ".plx",  ".pm",      ".pm",     ".pm4",   ".png",   ".pnm",  ".pnm",   ".pot",   ".pot",
    ".pov",  ".ppm",   ".ppt",  ".ppt",     ".pre",    ".pvu",   ".py",    ".pyc",  ".qcp",   ".qif",   ".qtc",
    ".ra",   ".ra",    ".ra",   ".ras",     ".ras",    ".ras",   ".rexx",  ".rf",   ".rgb",   ".rm",    ".rmi",
    ".rng",  ".rng",   ".rnx",  ".roff",    ".rp",     ".rt",    ".rt",    ".rtf",  ".rtf",   ".rv",    ".s3m",
    ".sbk",  ".scm",   ".scm",  ".scm",     ".scm",    ".sdp",   ".sdp",   ".sdr",  ".sea",   ".sea",   ".set",
    ".sgm",  ".sgm",   ".sh",   ".sh",      ".sh",     ".shtml", ".sid",   ".sit",  ".sit",   ".skd",   ".sl",
    ".smi",  ".snd",   ".sol",  ".spc",     ".spc",    ".spl",   ".spr",   ".src",  ".ssm",   ".sst",   ".step",
    ".stl",  ".stl",   ".stl",  ".sv4cpio", ".sv4crc", ".svr",   ".svr",   ".swf",  ".tar",   ".tbk",   ".tcl",
    ".tcl",  ".tcsh",  ".tex",  ".texi",    ".text",   ".tgz",   ".tif",   ".tif",  ".tsi",   ".tsp",   ".tsp",
    ".tsv",  ".uil",   ".uni",  ".unv",     ".ustar",  ".ustar", ".uu",    ".vcd",  ".vcs",   ".vda",   ".vdo",
    ".vew",  ".viv",   ".viv",  ".vmd",     ".vmf",    ".voc",   ".voc",   ".vos",  ".vox",   ".vqe",   ".vqf",
    ".vrml", ".vrml",  ".vrml", ".vrt",     ".vsd",    ".w60",   ".w61",   ".wav",  ".wav",   ".wb1",   ".wbmp",
    ".web",  ".wk1",   ".wmf",  ".wml",     ".wmlc",   ".wmls",  ".wmlsc", ".wp",   ".wpd",   ".wq1",   ".wri",
    ".wri",  ".wsc",   ".wtk",  ".xbm",     ".xbm",    ".xbm",   ".xdr",   ".xgz",  ".xif",   ".xl",    ".xls",
    ".xls",  ".xls",   ".xm",   ".xml",     ".xml",    ".xmz",   ".xpix",  ".xpm",  ".xsr",   ".xwd",   ".xwd",
    ".z",    ".zip",   ".zip",  ".zip",     ".zsh"};
}

zpt::MIMEType zpt::get_mime(string _in) {
	magic_t myt = magic_open(MAGIC_CONTINUE | MAGIC_ERROR | MAGIC_MIME);
	magic_load(myt, nullptr);

	string _mime(magic_file(myt, _in.data()));
	_mime.assign(_mime.substr(0, _mime.find(";")));
	magic_close(myt);

	for (size_t _i = 0; _i != _MIMETYPE_LEN; _i++) {
		if (_mime == string(zpt::mimetype_names[_i])) {
			return (zpt::MIMEType)_i;
		}
	}

	return zpt::application_octet_stream;
}

bool zpt::path_exists(string _in) {
	struct stat _buffer;
	return (stat(_in.data(), &_buffer) == 0);
}

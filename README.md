DLVHEX-SPARQL
=============

For Ubuntu:
==========

Qt:
===
Install Qt from: http://qt-project.org/downloads for Qt online installer.

Soprano:
========
git clone git://anongit.kde.org/soprano.git

Virtuoso:
=========
Download Virtuso 6.1.8
http://downloads.sourceforge.net/virtuoso/virtuoso-opensource-6.1.8.tar.gz
sed -i "s|virt_iodbc_dir/include|&/iodbc|" configure &&

./configure --prefix=/usr 
 --sysconfdir=/etc 
 --localstatedir=/var 
 --with-iodbc=/usr 
 --with-readline 
 --without-internal-zlib 
 --program-transform-name="s/isql/isql-v/" 
 --disable-all-vads 
 --disable-static &&
make

Now, as the root user:
sudo make install


How to install the DLVHEX-SPARQL Plugin:
========================================

sudo ./configure QT_CFLAGS=/opt/Qt/5.3/gcc_64/include/ QT_LIBS=/opt/Qt/5.3/gcc_64/lib PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

sudo make && sudo make install

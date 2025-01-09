from building import *
Import('rtconfig')
src   = []
cwd = GetCurrentDir()

# add libcrc src files.
if GetDepend('PKG_LIBCRC_CRC8'):
    src = Glob('src/crc8.c')

if GetDepend('PKG_LIBCRC_CRC16'):
    src += Glob('src/crc16.c')
    src += Glob('src/crcccitt.c')
    src += Glob('src/crcdnp.c')
    src += Glob('src/crcsick.c')
    src += Glob('src/crckrmit.c')

if GetDepend('PKG_LIBCRC_CRC32'):
    src += Glob('src/crc32.c')
    src += Glob('tab/gentab32.inc')
    
if GetDepend('PKG_LIBCRC_CRC64'):
    src += Glob('src/crc64.c')
    src += Glob('tab/gentab64.inc')

if GetDepend('PKG_USING_CHECKSUM_NMEA'):
    src += Glob('src/nmea-chk.c')

if GetDepend('PKG_USING_LIBCRC_SAMPLE'):
    src += Glob('examples/libcrc_sample.c')


# add mpu6xxx include path.
path  = [cwd + '/include']
# add src and include to group.
group = DefineGroup('libcrc', src, depend = ['PKG_USING_LIBCRC'], CPPPATH = path)

Return('group')
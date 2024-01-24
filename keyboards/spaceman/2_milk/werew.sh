
# Requires qmk arch pkg (will auto install all dependencies to cross-plat build arm)

# To compile
qmk compile -kb spaceman/2_milk -km werew

# To flash
# 1) Run
qmk flash -kb spaceman/2_milk -km werew -e CONVERT_TO=rp2040_ce

# 2) Ground reset pin to enter in boot mode (lsusb should show boot mode)
# 3) Mount USB drive (can use the GUI)

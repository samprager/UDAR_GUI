
BASEDIR=$(dirname "$0")
echo "fixing permissions in $BASEDIR/"

BASEDIR2=$(dirname "$(dirname "$BASEDIR")")
#echo "$BASEDIR2/"

#BASEDIR3=$BASEDIR2/build-UDAR_GUI-Desktop_Qt_5_7_0_clang_64bit-Debug
#echo "fixing permissions in $BASEDIR3/"

BASEDIR3=$BASEDIR/builds/build-UDAR_GUI-Desktop_Qt_5_7_0_GCC_64bit-Debug-OSX
echo "fixing permissions in $BASEDIR3/"

BASEDIR4=/Users/sam/.config/QtProject
echo "fixing permissions in $BASEDIR4/"

sudo chown -R sam ./$BASEDIR/
sudo chown -R sam ./$BASEDIR3/
sudo chown -R sam $BASEDIR4/

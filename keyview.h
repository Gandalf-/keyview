/* keyview.h
 *
 */

#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <string>
#include <iostream>

using namespace std;

enum STATE {S_ON, S_OFF, S_HOLD, S_NONE};

// mode keys
const string rct = "r_ctl";
const string lct = "l_ctl";
const string rsh = "r_shf";
const string lsh = "l_shf";
const string ral = "r_alt";
const string lal = "l_alt";

// special keys
const string _U_ = "???";
const string esc = "srh";
const string bks = "bks";
const string ent = "ret";
const string tab = "tab";
const string spc = "spc";
const string slh = "\\";
const string qot = "\"";
const string srh = "esc";
const string fn1 = "b_arw";
const string fn2 = "f_arw";
const string fn3 = "refresh";
const string fn4 = "fullscreen";
const string fn5 = "switcher";
const string fn6 = "b_down";
const string fn7 = "b_up";
const string fn8 = "mute";
const string fn9 = "s_down";
const string fn0 = "s_up";
const string pwr = "power";
const string lar = "l_arw";
const string uar = "u_arw";
const string dar = "d_arw";
const string rar = "r_arw";

const string keys[] = {
 /*  0 - 9  */ _U_,esc,"1","2","3","4","5","6","7","8",
 /* 10 - 19 */ "9","0","-","=",bks,tab,"q","w","e","r",
 /* 20 - 29 */ "t","y","u","i","o","p","[","]",ent,rct,
 /* 30 - 39 */ "a","s","d","f","g","h","j","k","l",";",
 /* 40 - 49 */ "'","`",rsh,slh,"z","x","c","v","b","n",
 /* 50 - 59 */ "m",",",".","/",lsh,_U_,ral,spc,_U_,fn1,
 /* 60 - 69 */ fn2,fn3,fn4,fn5,fn6,fn7,fn8,fn9,fn0,_U_,
 /* 70 - 79 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,
 /* 80 - 89 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,
 /* 90 - 99 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,lct,_U_,_U_,
 /*100 -109 */ lal,_U_,_U_,uar,_U_,lar,rar,_U_,dar,_U_,
 /*110 -119 */ _U_,_U_,_U_,_U_,_U_,_U_,pwr,_U_,_U_,_U_,
 /*120 -129 */ _U_,_U_,_U_,_U_,_U_,srh,_U_,_U_,_U_,_U_,
  };

const string shift_keys[] = {
 /*  0 - 9  */ _U_,esc,"!","@","#","$","%","^","&","*",
 /* 10 - 19 */ "(",")","_","+",bks,tab,"Q","W","E","R",
 /* 20 - 29 */ "T","Y","U","I","O","P","{","}",ent,rct,
 /* 30 - 39 */ "A","S","D","F","G","H","J","K","L",":",
 /* 40 - 49 */ qot,"~",rsh,"|","Z","X","C","V","B","N",
 /* 50 - 59 */ "M","<",">","?",lsh,_U_,ral,spc,_U_,fn1,
 /* 60 - 69 */ fn2,fn3,fn4,fn5,fn6,fn7,fn8,fn9,fn0,_U_,
 /* 70 - 79 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,
 /* 80 - 89 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,_U_,
 /* 90 - 99 */ _U_,_U_,_U_,_U_,_U_,_U_,_U_,lct,_U_,_U_,
 /*100 -109 */ lal,_U_,_U_,uar,_U_,lar,rar,_U_,dar,_U_,
 /*110 -119 */ _U_,_U_,_U_,_U_,_U_,_U_,pwr,_U_,_U_,_U_,
 /*120 -129 */ _U_,_U_,_U_,_U_,_U_,srh,_U_,_U_,_U_,_U_,
};

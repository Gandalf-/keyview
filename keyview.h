/* keyview.h
 *
 * Author: Austin Voecks
 */

#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <string>
#include <iostream>

enum STATE {S_ON, S_OFF, S_HOLD, S_NONE};

// mode keys
const std::string rct = "r_ctl";
const std::string lct = "l_ctl";
const std::string rsh = "r_shf";
const std::string lsh = "l_shf";
const std::string ral = "r_alt";
const std::string lal = "l_alt";

// special keys
const std::string _U_ = "???";
const std::string esc = "srh";
const std::string bks = "bks";
const std::string ent = "ret";
const std::string tab = "tab";
const std::string spc = "spc";
const std::string slh = "\\";
const std::string qot = "\"";
const std::string srh = "esc";
const std::string fn1 = "b_arw";
const std::string fn2 = "f_arw";
const std::string fn3 = "refresh";
const std::string fn4 = "fullscreen";
const std::string fn5 = "switcher";
const std::string fn6 = "b_down";
const std::string fn7 = "b_up";
const std::string fn8 = "mute";
const std::string fn9 = "s_down";
const std::string fn0 = "s_up";
const std::string pwr = "power";
const std::string lar = "l_arw";
const std::string uar = "u_arw";
const std::string dar = "d_arw";
const std::string rar = "r_arw";

const std::string keys[] = {
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

const std::string shift_keys[] = {
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

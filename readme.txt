## Scriven42's Modified RePhone Kit Create Source Code

-Added a keyboard to type new messages, not just send pre-written messages.

Keyboard Layout:
  Page 1         Page 2         Page 3         Page 4         Page 5
a  o  e  u     f  g  c  r     v  7  8  9     -  _  =  +     <  >  (  )
i  d  h  t     l  q  j  k     z  4  5  6     #  $  %  @     [  ]  \  |
n  s  p  y     x  b  m  w     !  1  2  3     &  *  :  ;     {  }  ^  `
. sp  ,  >     <  '  "  >     < sp  0  >     <  /  ?  >     <  ~ sp sp

Notes:
	sp = space
	<, > in purple, on the lower right and left corners, switches between pages.

---

If you want to install without compiling yourself, please try these steps:

1) Copy the "RePhone_Create_Source_Code/ARM/RePhone_Create_Source_Code_default.vxp" file to the "\MRE" subdirectory on your RePhone.
2) Edit the "autostart.txt" file to read:

			[autostart]
			App=C:\MRE\RePhone_Create_Source_Code_default.vxp

ELF          >    �      @       @8          @ 8  @         @       @       @       �      �                                                                                        X      X                                        =      =                                           T      T                   h-      h=      h=      �      �                   x-      x=      x=      �      �                   8      8      8      0       0                    h      h      h      D       D              S�td   8      8      8      0       0              P�td   p#      p#      p#      4       4              Q�td                                                  R�td   h-      h=      h=      �      �             /lib64/ld-linux-x86-64.so.2               GNU   �          � �                   GNU '��`å3Z�5�،� ��         GNU                                 �            �e�m                            $                      �                                             S                                            7                                            6                      �                       M                                                                                        Z                      �                       >   "                    puts exit fopen system atoi pclose __libc_start_main fprintf __cxa_finalize popen fclose fwrite libc.so.6 GLIBC_2.2.5 GLIBC_2.34 _ITM_deregisterTMCloneTable __gmon_start__ _ITM_registerTMCloneTable                            a          ui	   k      ���   w       h=             �      p=             @      @             @      �?                    �?                    �?         	           �?                    �?                    �?                    �?                    �?                    �?                    �?                    �?                    �?         
           �?                    �?                    �?                    �?                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ��H��H��/  H��t��H���     �5J/  �%L/  @ ��h    �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f���h   �b���f���h	   �R���f���h
   �B���f����%/  fD  ���%�.  fD  ���%~.  fD  ���%v.  fD  ���%n.  fD  ���%f.  fD  ���%^.  fD  ���%V.  fD  ���%N.  fD  ���%F.  fD  ���%>.  fD  ���%6.  fD  ��1�I��^H��H���PTE1�1�H�=�   �.  �f.�     H�=9.  H�2.  H9�tH��-  H��t	���    ��    H�=	.  H�5.  H)�H��H��?H��H�H��tH��-  H��t��fD  ��    ���=�-   u+UH�=�-   H��tH�=�-  �y����d�����-  ]� ��    ���w�����UH��H��@�}�H�u��}�tH�_  H���?����   �����H�t  H��H�l  H������H�E�H�}� uH�j  H�������   ����H�7  H��H�m  H���?���H�E�H�}� uH�m  H��������   �K���H�E�H��H� H���(����E�H�E�H��H� H�������E�H�E�H��H� H��������E��E�    �E�    �   �E�    �~�E�����}�ыE����E܉E��E�E�Й�}��9�uJ�E��}��  O�M��U܋E؉�H��  H�Ǹ    �1����M��U�H�E�H�5�  H�Ǹ    �3����E��E�;E��v������E��E�;E��Z���H�E�H�������H�E�H���   �   H�t  H���4���H�E�H���D   �   H�t  H������H�E�H���   �   H��  H��������U�H�E�H��  H��H�Ǹ    �����u�M�U�H�E�A��H�5�  H�Ǹ    �b����U�H�E�H��  H��H�Ǹ    �D���H�E�H���   �   H�  H���t���H�E�H���   �   H��  H���T���H�E�H���1   �   H��  H���4���H�E�H���   �   H��  H������H�E�H���   �   H��  H��������}�u�M�U�H�E�A��A��H�5�  H�Ǹ    �z����}�u�M�U�H�E�A��A��H�5�  H�Ǹ    �P����M�U�H�E�H�5�  H�Ǹ    �2���H�E�H������H�6  H��������    ����H��H���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         Error! Run $ ./elipticas_IsaacMenezes.x a b p w pontosElipticas.dat     Error on openning pontosElipticas.dat gnuplot -persistent       Error on openning gnuplot pipe G%d = (%d, %d)
 %d	%d
   set terminal wxt size 1700,850
 set multiplot layout 1,2 title 'Graphs: mod p and |R (reals field)'
 set xlabel 'x'
 set ylabel 'f(x) mod %d'
  set title 'Elliptc curve graph: y^2 = x^3 + %dx + %d (mod %d)'
 plot 'pontosElipticas.dat' u 1:2 w p lc rgb 'red' pt 7 t 'points', %d/2 w l lw 3 lc rgb 'green' t 'symmetry'
 set ylabel 'f(x)'
        set title 'Elliptc curve graph over the R field'
 set zeroaxis
 set samples 100000
     f(x) = (x**3 + %d*x + %d >=0) ? sqrt(x**3 + %d*x + %d) : 1/0
   fl(x) = (x**3 + %d*x + %d >=0) ? -sqrt(x**3 + %d*x + %d) : 1/0
 plot f(x) w l lw 2 lc rgb 'red' t 'y^2 = x^3 + %dx + %d', fl(x) w l lw 2 lc rgb 'red' notitle
 open pontosElipticas.dat ;4      ����h   p����   �����   0���P   ����              zR x�        ����&    D    $   4   @����    FJw� ?9*3$"       \   ����              t   �����              �   Q����   E�C�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         �      @             a                            0             h=                           p=                    ���o    �             p             �      
       �                                           h?                                        P             �             �       	                            ���o          ���o    `      ���o           ���o    8      ���o                                                                                           x=                      0      @      P      `      p      �      �      �      �      �      �                                                      @      GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0                                  ��                	     �                  ��                     �                                   3     @              I     @             U     p=              |     �              �     h=              �    ��                    ��                �     P$                   ��                �     x=              �      p#              �     h?                                                          �      @              9                     J    @              Q                     d   0              j                     �                     }                     �     @              �                     �                      �   @              �                   �    @              �    �      &       �    @              �    �      �      �                                                               '                     8                     K   @              W                      q  "                   �                   Scrt1.o __abi_tag crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.0 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry elipticas_IsaacMenezes.c __FRAME_END__ _DYNAMIC __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ __libc_start_main@GLIBC_2.34 _ITM_deregisterTMCloneTable puts@GLIBC_2.2.5 _edata fclose@GLIBC_2.2.5 _fini system@GLIBC_2.2.5 pclose@GLIBC_2.2.5 __data_start fprintf@GLIBC_2.2.5 __gmon_start__ __dso_handle _IO_stdin_used _end __bss_start main popen@GLIBC_2.2.5 fopen@GLIBC_2.2.5 atoi@GLIBC_2.2.5 exit@GLIBC_2.2.5 fwrite@GLIBC_2.2.5 __TMC_END__ _ITM_registerTMCloneTable __cxa_finalize@GLIBC_2.2.5 _init  .symtab .strtab .shstrtab .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt.got .plt.sec .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .dynamic .data .bss .comment                                                                                                                            #             8      8      0                              6             h      h      $                              I             �      �                                     W   ���o       �      �      $                             a             �      �      �                          i             p      p      �                              q   ���o       8      8      "                            ~   ���o       `      `      0                            �             �      �      �                            �      B       P      P                                �                                                         �                           �                             �             �      �                                   �             �      �      �                             �             �      �      �                             �             0      0                                    �                             p                             �             p#      p#      4                              �             �#      �#      �                              �             h=      h-                                   �             p=      p-                                   �             x=      x-      �                           �             h?      h/      �                                          @       0                                                @      0                                         0               0      +                                                   @0      P                          	                      �4      �                                                   "7                                   
 / / /  
 / / /   m a i n . c p p  
 / / /   S a n d b o x  
 / / /  
 / / /   A p a c h e   2 . 0   L I C E N S E .  
 / / /   R e f e r   t o   L I C E N S E . t x t   f o r   m o r e   d e t a i l s .  
 / / /  
  
 # i n c l u d e   < i o s t r e a m >  
  
 # i n c l u d e   < q s / c o r e / W i n d o w . h p p >  
 # i n c l u d e   < q s / u t i l s / E r r o r . h p p >  
  
 i n t   m a i n ( i n t   a r g s c ,   c h a r   * a r g s v [ ] )  
 {  
 	 t r y  
 	 {  
 	 	 / /   T r y   t o   i n i t   S D L 2   w i t h   p a s s e d   f l a g s ,   c h e c k i n g   t o   m a k e   s u r e   o f   s u c c e s s .  
 	 	 i f   ( S D L _ I n i t ( S D L _ I N I T _ E V E R Y T H I N G )   ! =   0 )  
 	 	 {  
 	 	 	 s t d : : c o u t   < <   " I n i t   f a i l e d .   S D L _ E r r o r :   "   < <   S D L _ G e t E r r o r ( )   < <   s t d : : e n d l ;  
 	 	 }  
 	 	 e l s e  
 	 	 {  
 	 	 	 / /   C r e a t e   w i n d o w   a n d   c h e c k   f o r   e r r o r s .  
 	 	 	 q s : : W i n d o w   w i n d o w ;  
 	 	 	 i f   ( ! w i n d o w . c r e a t e ( " T e s t B e d " ,   8 0 0 ,   6 0 0 ,   S D L _ W I N D O W _ A L L O W _ H I G H D P I ) )  
 	 	 	 {  
 	 	 	 	 s t d : : c o u t   < <   " W i n d o w   f a i l e d .   Q S _ E r r o r :   "   < <   q s : : E r r o r : : h a n d l e . c u r r e n t ( )   < <   s t d : : e n d l ;  
 	 	 	 }  
  
 	 	 	 / /   E v e n t s  
 	 	 	 S D L _ E v e n t   e ;  
  
 	 	 	 / /   L o o p  
 	 	 	 w h i l e   ( w i n d o w . i s O p e n ( ) )  
 	 	 	 {  
 	 	 	 	 S D L _ P o l l E v e n t ( & e ) ;  
  
 	 	 	 	 / /   H a n d l e   r e s i z i n g   a n d   q u i t t i n g   e v e n t s .  
 	 	 	 	 s w i t c h   ( e . t y p e )  
 	 	 	 	 {  
 	 	 	 	 c a s e   S D L _ Q U I T :  
 	 	 	 	 	 w i n d o w . c l o s e ( ) ;  
 	 	 	 	 	 b r e a k ;  
  
 	 	 	 	 c a s e   S D L _ K E Y D O W N :  
 	 	 	 	 	 s w i t c h   ( e . k e y . k e y s y m . s y m )  
 	 	 	 	 	 {  
 	 	 	 	 	 c a s e   S D L K _ E S C A P E :  
 	 	 	 	 	 	 w i n d o w . c l o s e ( ) ;  
 	 	 	 	 	 	 b r e a k ;  
 	 	 	 	 	 }  
  
 	 	 	 	 c a s e   S D L _ W I N D O W E V E N T _ S I Z E _ C H A N G E D :  
 	 	 	 	 	 w i n d o w . r e s i z e ( e . w i n d o w . d a t a 1 ,   e . w i n d o w . d a t a 2 ) ;  
 	 	 	 	 	 b r e a k ;  
 	 	 	 	 }  
  
 	 	 	 	 / /   R e n d e r .  
 	 	 	 	 w i n d o w . c l e a r ( q s : : C o l o u r {   0 . 0 f ,   1 . 0 f ,   0 . 0 f ,   1 . 0 f   } ) ;  
 	 	 	 	 w i n d o w . s w a p ( ) ;  
 	 	 	 }  
  
 	 	 	 w i n d o w . d e s t r o y ( ) ;  
  
 	 	 	 / /   E x i t  
 	 	 	 S D L _ Q u i t ( ) ;  
 	 	 }  
 	 }  
 	 c a t c h   ( c o n s t   s t d : : e x c e p t i o n &   e )  
 	 {  
 	 	 s t d : : c o u t   < <   " E X C E P T I O N   C A U G H T :   "   < <   e . w h a t ( )   < <   s t d : : e n d l ;  
 	 }  
 	 c a t c h   ( . . . )  
 	 {  
 	 	 s t d : : c o u t   < <   " I n v a l i d   e x c e p t i o n .   E n s u r e   e x c e p t i o n   i s   d e r i v e d   f r o m   s t d : : e x c e p t i o n . "   < <   s t d : : e n d l ;  
 	 }  
  
 	 r e t u r n   0 ;  
 }
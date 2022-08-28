;***********************************************************************************************************************
;*******************************        MONOPSYS: The MONOPOLY Expert System         ***********************************
;*******************************             Written by Chase Chemero                ***********************************
;*******************************     Based on the algorithms created by Gary Riley   ***********************************
;*******************************                  Written in CLIPS                   ***********************************
;*******************************                     08/10/2013                      ***********************************
;***********************************************************************************************************************
;***********************************************************************************************************************
;***********************************************************************************************************************
;***********************************************************************************************************************
;Welcome! This is a project that I did for my senior project at NYU. I studied the CLIPS language and created this 
;program. It is based on the algorithms written by Gary Riley in his book: Expert Systems: Principles and Programming,
;Fourth Edition. It is a great text if you are interested in learning more about expert systems or the CLIPS language.
;
;This program is an expert system that assists with playing and winning the Hasbro board game MONOPOLY.
;All you need to do to start the program is install the latest version of CLIPS and run the single
;command below. Everything else will take care of itself. Have fun trying this program out and let me know if you have 
;any feedback. I can be contacted at cac692@nyu.edu.
;***********************************************************************************************************************
;*******************          TO START, RUN THIS COMMAND AT THE CLIPS PROMPT         ***********************************
;******************* (batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\masterBatch1.c") **********************************
;***********************************************************************************************************************
;***********************************************************************************************************************
;ATTENTION! EVERYTHING FROM THIS POINT BELOW IS A PART OF THE PROGRAM. UNLESS YOU KNOW WWHAT YOU ARE DOING DO NOT ALTER
;OR RUN THIS CODE OUT OF ORDER. IT WILL CAUSE THE PROGRAM TO MALFUNCTION.
;
;
;
;
;
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\support1.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\controlEngine1.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE1.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE2.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE3.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE4.c")
;-----------------------------------------------------------------------------------------------------------------------
(batch "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE5.c")
;-----------------------------------------------------------------------------------------------------------------------
;The remaining code will clear the dialog box and prepare the application for use
;reset -> to be activated -> reset the application so that the agenda is loaded with initial rules
(reset)
;unwatch -> to be activated -> stop watching activations
(unwatch all)
;run -> to be activated -> run the program
;clear-window --> to be activated --> clear dialog window
(clear-window)
(run)

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
;This stage is simple. Its only purpose is to confirm that the player has finished his turn. Once the confirmation has 
;been given then the application can be reset and the whole process can begin again. A more advanced expert system could
;chronicle all user decisions for a more holistic approach to gameplay simulation and strategy development. The purpose
;of this program was just to become familiar with the CLIPS syntax and learn a few different algorithms that are popular
;in the field of AI.
;***********************************************************************************************************************
(defrule STAGE5::STAGE5-complete
	(declare (auto-focus TRUE))
	;LHS --> confirm the current stage is STAGE5
	?current-stage-check <- (stage-sequence STAGE5 $?subsequent-stages)
	?stage-completed <- (stage-completion FALSE)
	=>
	;RHS --> query whether player has completed STAGE1-STAGE4 (thereby completing STAGE5)
	(retract ?stage-completed)
	(printout t crlf "Initializing STAGE5: End Turn." crlf "---------------------------------------------------------------------------------------------------" crlf)
	(printout t "Have you finished your turn? (yes) or (no): ")
	(bind ?response (read))
	(while (neq ?response yes)
		do
		(printout t "Finish your turn. Is it over? (yes) or (no): ")
		(bind ?response (read)))
	(if (eq ?response yes)
		then (assert (stage-completion TRUE))
		(reset)
		(run)))
;***********************************************************************************************************************

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
;This stage is dedicated to beginning the turn and rolling the dice. All that the player needs to do is roll the dice in
;order to proceed to the next stage. The LHS looks to see that the current stage is STAGE1 and that the stage completion
;variable has been set to false (meaning the stage isn't complete).
;***********************************************************************************************************************
(defrule STAGE1::STAGE1-complete
	(declare (auto-focus TRUE))
	;LHS --> confirm the current stage is STAGE1
	?current-stage-check <- (stage-sequence STAGE1 $?subsequent-stages)
	?stage-completed <- (stage-completion FALSE)
	=>
	;RHS --> query whether player has rolled the dice (thereby completing this stage)
	(retract ?stage-completed)
	(printout t crlf "***************************************************************************************************" crlf "Initializing STAGE1: Begin Turn." crlf "---------------------------------------------------------------------------------------------------" crlf)
	(printout t "Did you roll the dice? (yes) or (no): ")
	(bind ?response (read))
	(while (neq ?response yes)
		do
		(printout t "Roll the dice. Did you roll? (yes) or (no): ")
		(bind ?response (read)))
	(if (eq ?response yes)
		then (assert (stage-completion TRUE))))
;***********************************************************************************************************************

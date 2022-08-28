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
;This stage takes is built in a procedural programming style. The purpose of this stage is to advise the player how he
;should approach different circumstances that can occur directly after rolling the dice and landing on a new square. If
;he lands on a space that is already owned and he can pay the rent then he has no choice but to do so. If he can't pay 
;then it is game over. If the property deed is unsold then he should purchase the property if he can afford it. The
;strategy used here is common strategy among veteran MONOPOLY players; purchase as much property as possible, even if
;it requires you mortgage your pre-existing properties.
;***********************************************************************************************************************
(defrule STAGE2::STAGE2-complete
	(declare (auto-focus TRUE))
	;LHS --> confirm the current stage is STAGE2
	?current-stage-check <- (stage-sequence STAGE2 $?subsequent-stages)
	?stage-completed <- (stage-completion FALSE)
	=>
	;RHS --> query what the status is of the space the player landed on (vacant or owned)
	(retract ?stage-completed)
	(printout t crlf "Initializing STAGE2: Purchase Properties." crlf "---------------------------------------------------------------------------------------------------" crlf)
	(printout t "Is the property you landed on vacant? (yes) or (no): ")
	(bind ?response (read))
	(if (eq ?response yes)
		then (printout t "Can you afford to purchase the property? (yes) or (no): ")
			(bind ?response (read))
			(if (eq ?response yes)
				then (printout t "Purchase the property." crlf crlf)
				(printout t "Initializing STAGE3: Trade Properties." crlf "---------------------------------------------------------------------------------------------------" crlf)
				else (printout t "Don't purchase the property." crlf crlf)
				(printout t "Initializing STAGE3: Trade Properties." crlf "---------------------------------------------------------------------------------------------------" crlf))
	else (printout t "Do you have enough money to pay the rent? (yes) or (no): ")
			(bind ?response (read))
			(if (eq ?response yes)
				then (printout t "Pay the rent." crlf crlf)
				(printout t "Initializing STAGE3: Trade Properties." crlf "---------------------------------------------------------------------------------------------------" crlf)
				else (printout t "Game over. You lose. Declare bankruptcy." crlf crlf)
				(halt)))
	(assert (stage-completion TRUE)))
;***********************************************************************************************************************

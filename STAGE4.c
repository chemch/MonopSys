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
;This stage is my favorite. It uses a decision tree algorithm that is shared in Gary Riley's book, Expert Systems: 
;Principles and Programming, Fourth Edition. It has simple functionality in that there is no ability to alter the
;decision tree. More advanced versions of this algorithm can query a user whether the expert system provided the correct
;answer.
;***********************************************************************************************************************
(defrule STAGE4::STAGE4-initialization
	(declare (auto-focus TRUE))
	;LHS --> initialize the root node (first question)
	?current-stage-check <- (stage-sequence STAGE4 $?subsequent-stages)
	?stage-completed <- (stage-completion FALSE)
	=>
	(retract ?stage-completed)
	(printout t crlf "Initializing STAGE4: Develop Properties." crlf "---------------------------------------------------------------------------------------------------" crlf)
	(load-facts "C:\\MONOPSYS\\MONOPSYS_SourceCode\\STAGE4Questions.dat")
	(assert (current-node root)))
;
;-----------------------------------------------------------------------------------------------------------------------	
(deffunction STAGE4::ask-TRUE-or-FALSE (?question)
	(printout t ?question " (yes) or (no): ")
	(bind ?answer (read))
	(while (and (neq ?answer yes) (neq ?answer no))
		(printout t ?question " (yes) or (no): ")
		(bind ?answer (read)))
	(if (eq ?answer yes)
		then (return TRUE)
		else (return FALSE)))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule STAGE4::prompt-decision-node-question
	?node <- (current-node ?name)
	(node (name ?name)
		(type decision)
		(question ?question))
	(not (answer ?))
	=>
	(assert (answer (ask-TRUE-or-FALSE ?question))))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule STAGE4::continue-to-TRUE-branch
	?node <- (current-node ?name)
	(node (name ?name)
		(type decision)
		(TRUE-node ?TRUE-branch))
	?answer <- (answer TRUE)
	=>
	(retract ?node ?answer)
	(assert (current-node ?TRUE-branch)))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule STAGE4::continue-to-FALSE-branch
	?node <- (current-node ?name)
	(node (name ?name)
		(type decision)
		(FALSE-node ?FALSE-branch))
	?answer <- (answer FALSE)
	=>
	(retract ?node ?answer)
	(assert (current-node ?FALSE-branch)))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule STAGE4::provide-answer-node
	?node <- (current-node ?name)
	(node (name ?name) (type answer) (answer ?answer-value))
	(not (answer ?))
	=>
	(printout t ?answer-value crlf)
	(assert (answer FALSE)))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule STAGE4::end-STAGE4
	?node <- (current-node ?name)
	(node (name ?name) (type answer))
	?answer <- (answer FALSE)
	=>
	(retract ?answer ?node)
	(assert (stage-completion TRUE)))
;***********************************************************************************************************************

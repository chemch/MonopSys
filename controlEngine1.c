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
;This purpose of this stage is to create a control structure. Despite the fact that CLIPS is not a procedural language
;does not mean that we can't artificially add procedural elements to the program. The way the program works is by 
;cycling through stages 1 through 5. This section of code creates the means by which we acknowledge the end of one stage
;and the beginning of another.
;
;Also, all modules are defined in this file. Facts that are to be included in the MAIN defmodule are included in this
;file as well.
;***********************************************************************************************************************
(deffacts MAIN::control-engine
	(stage-sequence STAGE1 STAGE2 STAGE3 STAGE4 STAGE5))
;
;-----------------------------------------------------------------------------------------------------------------------
(deftemplate MAIN::stage-complete
	(slot stage-completion (type SYMBOL) (allowed-symbols TRUE FALSE)))
;
(deffacts MAIN::initial-stage-settings
	(stage-completion FALSE))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule STAGE3
	(export deftemplate sequence objective element))
;	
(deftemplate STAGE3::sequence
   (multislot if)
   (multislot then))
;
(deftemplate STAGE3::element 
   (slot name)
   (slot value))
;
(deftemplate STAGE3::objective 
   (slot element))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule MAIN
	(export deftemplate stage-sequence)
	(export deftemplate stage-completion)
	(export deftemplate initial-fact)
	(import STAGE3 deftemplate sequence objective))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule STAGE1
	(import MAIN deftemplate stage-sequence)
	(import MAIN deftemplate stage-completion)
	(import MAIN deftemplate initial-fact))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule STAGE2
	(import MAIN deftemplate stage-sequence)
	(import MAIN deftemplate stage-completion))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule STAGE4
	(import MAIN deftemplate stage-sequence)
	(import MAIN deftemplate stage-completion))
;
;STAGE4 decision tree template
(deftemplate STAGE4::node
	(slot name)
	(slot type)
	(slot question)
	(slot TRUE-node)
	(slot FALSE-node)
	(slot answer))
;
;-----------------------------------------------------------------------------------------------------------------------
(defmodule STAGE5
	(import MAIN deftemplate stage-sequence)
	(import MAIN deftemplate stage-completion))
;
;-----------------------------------------------------------------------------------------------------------------------
(defrule MAIN::change-stage
	;LHS --> store stage conditions in a variable (stage-order) and check to see that the current stage is complete
	?stage-order <- (stage-sequence ?next-stage $?subsequent-stages)
	?stage-completed <- (stage-completion TRUE)
	=>
	;RHS --> move focus to the next stage and order the variable (stage-order) to reflect the proper order of stages
	(retract ?stage-completed)
	(retract ?stage-order)
	(assert (stage-completion FALSE))
	(assert (stage-sequence ?subsequent-stages ?next-stage)))
;
;***********************************************************************************************************************

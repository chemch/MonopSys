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
;Whereas the last stage was developed in a very procedural manner, this stage is fundamentally different in that it uses
;a backward chaining algorithm created by Gary Riley. Although CLIPS is not compatible with backward chaining theorems
;its flexibility allows users the ability to create their own program flow. The idea used here is that any forward
;chaining algorithm uses deduction and probability whereas any backward chaining algorithm uses induction and likelihood.
;There are some enhancements that could be added here. One additional capability that could be added is a calculation of
;likelihood that explains with what degree of certainty a combination of certain premises resulted in an event. Because
;there are no overlapping entirely overlapping premises, this functionality has been omitted. 
;
;Do note that there are certain conditions of patterns that are common across multiple many patterns (for example "Do
;you have any money to invest" is usually a prerequisite for any decision that might cost the player money, whether it 
;be purchasing property, trading or developing.
;***********************************************************************************************************************
(defmodule STAGE3 
   (export deftemplate sequence objective element))

(deftemplate STAGE3::sequence
   (multislot if)
   (multislot then))

(deftemplate STAGE3::element 
   (slot name)
   (slot value))

(deftemplate STAGE3::objective 
   (slot element))

(defrule STAGE3::attempt-sequence
   (objective (element ?obj-name))
   (sequence (if ?ele-name $?)
         (then ?obj-name $?))
   (not (element (name ?ele-name)))
   (not (objective (element ?ele-name)))
   =>
   (assert (objective (element ?ele-name))))

(defrule STAGE3::ask-element-value
   ?objective <- (objective (element ?obj-name))
   (not (element (name ?obj-name)))
   (not (sequence (then ?obj-name $?)))
   =>
   (retract ?objective)
   (printout t ?obj-name)
   (assert (element (name ?obj-name) 
                      (value (read)))))

(defrule STAGE3::objective-completed
   (declare (salience 100))
   ?objective <- (objective (element ?obj-name))
   (element (name ?obj-name))
   ?value <- (element (value ?obj-value))
   =>
   (retract ?objective)
   (printout t ?obj-value crlf))

(defrule STAGE3::sequence-completed
   (declare (salience 100))
   (objective (element ?obj-name))
   (element (name ?ele-name)
              (value ?ele-value))
   ?sequence <- (sequence (if ?ele-name is ?ele-value) 
                  (then ?obj-name is ?obj-value))
   =>
   (retract ?sequence)
   (assert (element (name ?obj-name) 
                      (value ?obj-value))))

(defrule STAGE3::remove-sequence-no-match
   (declare (salience 100))
   (objective (element ?obj-name))
   (element (name ?ele-name) (value ?ele-value))
   ?sequence <- (sequence (if ?ele-name is ~?ele-value) 
                  (then ?obj-name is ?obj-value))
   =>
   (retract ?sequence))

(defrule STAGE3::modify-sequence-match
   (declare (salience 100))
   (objective (element ?obj-name))
   (element (name ?ele-name) (value ?ele-value))
   ?sequence <- (sequence (if ?ele-name is ?ele-value and 
                      $?rest-if) 
                  (then ?obj-name is ?obj-value))
   =>
   (retract ?sequence)
   (modify ?sequence (if $?rest-if)))

(defmodule MAIN (import STAGE3 deftemplate sequence objective))

(deffacts MAIN::trade-rules
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is orange and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 50% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is orange and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 35% mark-up (including cash only) to your opponent. "))
					
	(sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is red and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 50% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is red and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 35% mark-up (including cash only) to your opponent. "))

   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "light blue" and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 45% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "light blue" and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 30% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is yellow and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 45% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is yellow and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 30% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "dark blue" and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 40% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "dark blue" and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 25% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "light purple" and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 40% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "light purple" and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 25% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is green and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 35% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is green and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 20% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "dark purple" and
				"Have you attempted a trade for this property? (yes) or (no): " is yes) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 35% mark-up (including both cash and property) to your opponent. "))
		 
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is yes and
				"According to Diagram #1 what is the highest ROI color group included in your previous answer? (orange), (red), (\"light blue\"), (yellow), (\"dark blue\"), (\"light purple\"), (green), or (\"dark purple\"): " is "dark purple" and
				"Have you attempted a trade for this property? (yes) or (no): " is no) 
					(then recommendation is "Attempt to procure this property through trade. Offer a 20% mark-up (including cash only) to your opponent. "))
					
   (sequence (if "Are there any color groups for which you are one property away from a monopoly in? (yes) or (no): " is no) 
         (then recommendation is "Do no attempt to trade. "))
		 
	(sequence (if "Will you win next time you collect your salary? (yes) or (no): " is yes) 
         (then recommendation is "Do no attempt to trade. ")))

(deffacts MAIN::initial-objective
   (objective (element recommendation)))

(defrule MAIN::start-STAGE3
	?current-stage-check <- (stage-sequence STAGE3 $?subsequent-stages)
	?stage-completed <- (stage-completion FALSE)
   =>
   (retract ?stage-completed)
   (focus STAGE3)
   (assert (stage-completion TRUE)))
;***********************************************************************************************************************

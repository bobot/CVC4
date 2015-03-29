; EXPECT: unknown
(set-logic UFDTLRA)
(set-info :smt-lib-version 2.0)
(set-info :category "crafted")
(set-info :status unknown)

(declare-datatypes () (
   ( Unit
     (U)
   )
))

(declare-datatypes (a) (
  ( List
    (Cons (hd a) (tail (List a)))
    (Nil (punit Unit))
   )
))


(declare-fun length (par (a) ((List a)) Real))

(assert (par (a) (forall ((u Unit)) (= (length (as (Nil u) (List a))) 0))))
(assert (par (a) (forall ((x a)(l (List a))) (= (length (Cons x l)) (+ 1 (length l))))))

(declare-sort I1 0)
(declare-fun y1 () I1)
(declare-fun y2 () I1)


(assert (not (= (length (Cons y1 (Cons y2 (as (Nil U) (List I1))))) 3)))



(check-sat)
(exit)
## Example:

```assembly
add  r1, r1, r2
sd   r1, addr
ld   r1, addr
addi r1, r1, 2

      ||
      \/

(declare-const r1    (_ BitVec 8))
(declare-const r2    (_ BitVec 8))
(declare-const r3    (_ BitVec 8))
(declare-const r4    (_ BitVec 8))
(declare-const r5    (_ BitVec 8))
(declare-const addr  (_ BitVec 8))

(declare-const ar    (Array (_ BitVec 8) (_ BitVec 8)))

(assert (= (bvadd r1 r2) r3))
(assert (= (store ar addr r3) ar))
(assert (= (select ar addr) r4))
(assert (= (bvadd r4 #x02) r5))

(check-sat)
(get-model)
```

The result that SMT returns:

```assembly
sat
(model
  (define-fun addr () (_ BitVec 8)
    #x00)
  (define-fun ar () (Array (_ BitVec 8) (_ BitVec 8))
    (_ as-array k!3))
  (define-fun r5 () (_ BitVec 8)
    #x02)
  (define-fun r2 () (_ BitVec 8)
    #x00)
  (define-fun r1 () (_ BitVec 8)
    #x00)
  (define-fun r4 () (_ BitVec 8)
    #x00)
  (define-fun r3 () (_ BitVec 8)
    #x00)
  (define-fun k!3 ((x!0 (_ BitVec 8))) (_ BitVec 8)
    (ite (= x!0 #x00) #x00
      #x00))
)
```

Now, based on the model above we can try if two variables `r1` and `r3` have always the same value by adding `(assert (not (= r3 r4)))` and then checking the satisfiability of the query:

```assembly
(declare-const r1    (_ BitVec 8))
(declare-const r2    (_ BitVec 8))
(declare-const r3    (_ BitVec 8))
(declare-const r4    (_ BitVec 8))
(declare-const r5    (_ BitVec 8))
(declare-const addr  (_ BitVec 8))

(declare-const ar    (Array (_ BitVec 8) (_ BitVec 8)))

(assert (= (bvadd r1 r2) r3))
(assert (= (store ar addr r3) ar))
(assert (= (select ar addr) r4))
(assert (= (bvadd r4 #x02) r5))

(assert (not (= r3 r4)))

(check-sat)
```

The results returned by the SMT solver is `unsat`; This shows that never these two variables can contain different values.
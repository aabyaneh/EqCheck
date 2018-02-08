#include "z3libs.h"

void prove_equivalence() {
  Z3_context ctx = mk_context();
  Z3_solver s = mk_solver(ctx);
  Z3_sort bv_sort, array_sort;

  Z3_ast r1, r2, r3, r4, r5, r6, s0;
  Z3_ast M, M1;
  Z3_ast c0, c1, c2, c3;
  Z3_ast addr_1, addr_2, addr_3, addr_4;

  bv_sort     = Z3_mk_bv_sort(ctx, 64);
  array_sort  = Z3_mk_array_sort(ctx, bv_sort, bv_sort);

  ////
  // Source code
  ////
  M           = mk_var(ctx, "M", array_sort);
  s0          = mk_var(ctx, "s0", bv_sort);
  r1          = mk_var(ctx, "r1", bv_sort);
  r2          = mk_var(ctx, "r2", bv_sort);
  r3          = mk_var(ctx, "r3", bv_sort);
  r4          = mk_var(ctx, "r4", bv_sort);
  r5          = mk_var(ctx, "r5", bv_sort);
  r6          = mk_var(ctx, "r6", bv_sort);

  c0          = Z3_mk_numeral(ctx, "0", bv_sort);
  c1          = Z3_mk_numeral(ctx, "1", bv_sort);
  c2          = Z3_mk_numeral(ctx, "2", bv_sort);
  c3          = Z3_mk_numeral(ctx, "3", bv_sort);

  addr_1      = mk_var(ctx, "addr_1", bv_sort);
  addr_1      = Z3_mk_bvsub(ctx, s0, c3);
  r1          = Z3_mk_select(ctx, M, addr_1);

  addr_2      = mk_var(ctx, "addr_2", bv_sort);
  addr_2      = Z3_mk_bvadd(ctx, r1, c0);
  r2          = Z3_mk_select(ctx, M, addr_2);

  r3          = Z3_mk_bvmul(ctx, r2, c2);

  r4          = Z3_mk_select(ctx, M, addr_1);

  addr_3      = mk_var(ctx, "addr_3", bv_sort);
  addr_3      = Z3_mk_bvadd(ctx, r4, c0);
  M1          = Z3_mk_store(ctx, M, addr_3, r3);

  r5          = Z3_mk_select(ctx, M1, addr_1);

  addr_4      = mk_var(ctx, "addr_4", bv_sort);
  addr_4      = Z3_mk_bvadd(ctx, r5, c1);

  r6          = Z3_mk_select(ctx, M1, addr_4);

  M1          = Z3_mk_store(ctx, M1, addr_1, r6);


  ////
  // rewrite code
  ////
  Z3_ast rp1, rp2, rp3, a0;
  Z3_ast Mp1;
  Z3_ast addrp_1, addrp_2;

  a0          = mk_var(ctx, "a0", bv_sort);
  rp1         = mk_var(ctx, "rp1", bv_sort);
  rp2         = mk_var(ctx, "rp2", bv_sort);
  rp3         = mk_var(ctx, "rp3", bv_sort);

  a0          = Z3_mk_select(ctx, M, addr_1);
  addrp_1     = mk_var(ctx, "addrp_1", bv_sort);
  addrp_1     = Z3_mk_bvadd(ctx, a0, c0);
  rp1         = Z3_mk_select(ctx, M, addrp_1);

  rp2         = Z3_mk_bvshl(ctx, rp1, c1);

  Mp1         = Z3_mk_store(ctx, M, addrp_1, rp2);

  addrp_2     = mk_var(ctx, "addrp_2", bv_sort);
  addrp_2     = Z3_mk_bvadd(ctx, a0, c1);
  rp3         = Z3_mk_select(ctx, Mp1, addrp_2);

  Mp1         = Z3_mk_store(ctx, Mp1, addr_1, rp3);


  // Precondition relations
  Z3_solver_assert(ctx, s, Z3_mk_eq(ctx, a0, Z3_mk_select(ctx, M, addr_1)));
  Z3_solver_assert(ctx, s, Z3_mk_not(ctx, Z3_mk_eq(ctx, addr_1, Z3_mk_select(ctx, M, addr_1))));

  // Proof obligation 1
  Z3_ast add_eq1 = Z3_mk_eq(ctx, addr_3, addrp_1);
  Z3_ast val_eq1 = Z3_mk_eq(ctx, Z3_mk_select(ctx, M1, addr_3), Z3_mk_select(ctx, Mp1, addrp_1));
  Z3_ast thm1    = Z3_mk_implies(ctx, add_eq1, val_eq1);
  prove(ctx, s, thm1, Z3_TRUE);

  // Proof obligation 2
  Z3_ast add_eq2 = Z3_mk_eq(ctx, addr_1, addr_1);
  Z3_ast val_eq2 = Z3_mk_eq(ctx, Z3_mk_select(ctx, M1, addr_1), Z3_mk_select(ctx, Mp1, addr_1));
  Z3_ast thm2    = Z3_mk_implies(ctx, add_eq2, val_eq2);
  prove(ctx, s, thm2, Z3_TRUE);
}

int main () {

  prove_equivalence();

  return 0;
}
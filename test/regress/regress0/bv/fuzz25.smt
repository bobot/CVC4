(benchmark fuzzsmt
:logic QF_BV
:status unsat
:extrafuns ((v0 BitVec[4]))
:extrafuns ((v1 BitVec[4]))
:extrafuns ((v2 BitVec[4]))
:formula
(let (?e3 bv2[4])
(let (?e4 bv3[4])
(let (?e5 bv15[4])
(let (?e6 bv13[4])
(let (?e7 (ite (bvule v0 ?e3) bv1[1] bv0[1]))
(let (?e8 (zero_extend[0] v1))
(let (?e9 (bvnor v0 v1))
(let (?e10 (bvneg v1))
(let (?e11 (bvxnor ?e8 v1))
(let (?e12 (ite (bvugt ?e5 ?e11) bv1[1] bv0[1]))
(let (?e13 (ite (bvugt ?e10 ?e11) bv1[1] bv0[1]))
(let (?e14 (repeat[1] v1))
(let (?e15 (ite (= ?e5 ?e5) bv1[1] bv0[1]))
(let (?e16 (bvnot ?e14))
(let (?e17 (ite (bvslt ?e11 (sign_extend[3] ?e7)) bv1[1] bv0[1]))
(let (?e18 (ite (bvule ?e4 ?e16) bv1[1] bv0[1]))
(let (?e19 (ite (bvsge v1 (sign_extend[3] ?e18)) bv1[1] bv0[1]))
(let (?e20 (ite (= v0 (sign_extend[3] ?e15)) bv1[1] bv0[1]))
(let (?e21 (ite (bvule ?e3 v0) bv1[1] bv0[1]))
(let (?e22 (ite (bvsgt ?e16 ?e9) bv1[1] bv0[1]))
(let (?e23 (extract[0:0] ?e21))
(let (?e24 (bvnot ?e10))
(let (?e25 (rotate_right[0] ?e17))
(let (?e26 (bvnand v0 ?e11))
(let (?e27 (ite (bvult ?e7 ?e25) bv1[1] bv0[1]))
(let (?e28 (bvmul (sign_extend[3] ?e7) v1))
(let (?e29 (ite (= bv1[1] (extract[1:1] ?e8)) (zero_extend[3] ?e20) ?e26))
(let (?e30 (ite (= bv1[1] (extract[0:0] ?e12)) ?e29 (zero_extend[3] ?e12)))
(let (?e31 (bvsub v0 ?e28))
(let (?e32 (bvand v1 (zero_extend[3] ?e20)))
(let (?e33 (bvcomp (sign_extend[3] ?e27) v1))
(let (?e34 (ite (= (zero_extend[3] ?e19) ?e11) bv1[1] bv0[1]))
(let (?e35 (bvashr ?e34 ?e20))
(let (?e36 (bvadd ?e31 (sign_extend[3] ?e19)))
(let (?e37 (bvashr ?e32 (zero_extend[3] ?e19)))
(let (?e38 (repeat[1] ?e30))
(let (?e39 (bvand ?e3 (zero_extend[3] ?e15)))
(let (?e40 (ite (bvult ?e12 ?e17) bv1[1] bv0[1]))
(let (?e41 (ite (distinct ?e39 ?e28) bv1[1] bv0[1]))
(let (?e42 (extract[1:1] ?e14))
(let (?e43 (rotate_right[2] ?e29))
(let (?e44 (bvand (sign_extend[3] ?e13) ?e4))
(let (?e45 (bvsub ?e29 (zero_extend[3] ?e35)))
(let (?e46 (bvlshr v0 (zero_extend[3] ?e20)))
(let (?e47 (bvsub ?e41 ?e17))
(let (?e48 (bvnor ?e29 (zero_extend[3] ?e18)))
(let (?e49 (ite (bvsle ?e25 ?e12) bv1[1] bv0[1]))
(let (?e50 (ite (bvsle (sign_extend[3] ?e35) ?e31) bv1[1] bv0[1]))
(let (?e51 (zero_extend[0] ?e31))
(let (?e52 (ite (bvugt v2 (sign_extend[3] ?e15)) bv1[1] bv0[1]))
(let (?e53 (bvshl ?e16 (sign_extend[3] ?e47)))
(let (?e54 (ite (= ?e44 v0) bv1[1] bv0[1]))
(let (?e55 (bvshl (zero_extend[3] ?e34) ?e44))
(let (?e56 (bvmul ?e10 ?e36))
(let (?e57 (ite (= ?e38 (sign_extend[3] ?e27)) bv1[1] bv0[1]))
(let (?e58 (bvadd (sign_extend[3] ?e13) ?e36))
(let (?e59 (repeat[1] ?e5))
(let (?e60 (ite (bvule ?e9 (zero_extend[3] ?e12)) bv1[1] bv0[1]))
(let (?e61 (ite (bvuge v1 (sign_extend[3] ?e19)) bv1[1] bv0[1]))
(let (?e62 (bvnot ?e33))
(let (?e63 (bvnand ?e49 ?e25))
(let (?e64 (ite (bvugt (sign_extend[3] ?e62) ?e44) bv1[1] bv0[1]))
(let (?e65 (ite (bvslt (sign_extend[3] ?e33) ?e8) bv1[1] bv0[1]))
(let (?e66 (ite (bvsge ?e6 ?e11) bv1[1] bv0[1]))
(flet ($e67 (bvugt ?e13 ?e65))
(flet ($e68 (bvslt ?e58 ?e48))
(flet ($e69 (bvult ?e32 ?e10))
(flet ($e70 (bvugt v1 (zero_extend[3] ?e66)))
(flet ($e71 (distinct ?e28 ?e51))
(flet ($e72 (bvult ?e32 (zero_extend[3] ?e23)))
(flet ($e73 (= ?e9 ?e9))
(flet ($e74 (bvsle ?e65 ?e50))
(flet ($e75 (bvslt ?e32 (sign_extend[3] ?e40)))
(flet ($e76 (bvult ?e20 ?e7))
(flet ($e77 (bvule ?e24 (sign_extend[3] ?e19)))
(flet ($e78 (bvsgt ?e39 (zero_extend[3] ?e18)))
(flet ($e79 (bvuge ?e22 ?e25))
(flet ($e80 (= ?e3 ?e10))
(flet ($e81 (bvule ?e43 (sign_extend[3] ?e7)))
(flet ($e82 (bvugt ?e55 ?e44))
(flet ($e83 (bvslt ?e51 ?e30))
(flet ($e84 (= ?e32 (zero_extend[3] ?e40)))
(flet ($e85 (bvugt (sign_extend[3] ?e35) ?e48))
(flet ($e86 (distinct ?e6 ?e32))
(flet ($e87 (distinct (sign_extend[3] ?e19) ?e32))
(flet ($e88 (bvsgt ?e32 (zero_extend[3] ?e65)))
(flet ($e89 (bvugt ?e21 ?e13))
(flet ($e90 (= v0 (zero_extend[3] ?e13)))
(flet ($e91 (bvsgt (sign_extend[3] ?e64) ?e14))
(flet ($e92 (distinct ?e58 (zero_extend[3] ?e21)))
(flet ($e93 (bvule (zero_extend[3] ?e66) ?e28))
(flet ($e94 (bvugt ?e24 ?e37))
(flet ($e95 (bvule v0 (sign_extend[3] ?e60)))
(flet ($e96 (bvslt ?e5 (zero_extend[3] ?e40)))
(flet ($e97 (bvule ?e27 ?e17))
(flet ($e98 (= ?e17 ?e47))
(flet ($e99 (bvsge ?e53 v2))
(flet ($e100 (bvsle (sign_extend[3] ?e35) ?e32))
(flet ($e101 (bvugt ?e24 (zero_extend[3] ?e15)))
(flet ($e102 (bvugt ?e52 ?e50))
(flet ($e103 (bvuge v2 (sign_extend[3] ?e57)))
(flet ($e104 (bvule ?e35 ?e57))
(flet ($e105 (bvsgt (sign_extend[3] ?e62) ?e4))
(flet ($e106 (bvsgt ?e9 v2))
(flet ($e107 (bvsge ?e56 (zero_extend[3] ?e52)))
(flet ($e108 (bvsle ?e21 ?e27))
(flet ($e109 (bvsge ?e58 ?e30))
(flet ($e110 (bvsgt ?e23 ?e40))
(flet ($e111 (distinct ?e20 ?e40))
(flet ($e112 (bvsge ?e9 ?e28))
(flet ($e113 (bvule ?e32 ?e37))
(flet ($e114 (bvsge (sign_extend[3] ?e15) ?e8))
(flet ($e115 (bvsgt ?e46 (sign_extend[3] ?e27)))
(flet ($e116 (distinct (sign_extend[3] ?e49) ?e30))
(flet ($e117 (bvugt (zero_extend[3] ?e27) ?e26))
(flet ($e118 (bvule (zero_extend[3] ?e64) ?e5))
(flet ($e119 (bvugt v0 ?e29))
(flet ($e120 (bvsgt ?e34 ?e17))
(flet ($e121 (distinct ?e6 (sign_extend[3] ?e50)))
(flet ($e122 (bvult (zero_extend[3] ?e7) ?e39))
(flet ($e123 (bvsgt ?e26 ?e4))
(flet ($e124 (bvslt ?e11 ?e30))
(flet ($e125 (bvuge ?e28 ?e6))
(flet ($e126 (= ?e55 (sign_extend[3] ?e42)))
(flet ($e127 (bvugt ?e29 (zero_extend[3] ?e27)))
(flet ($e128 (bvsge ?e6 (sign_extend[3] ?e50)))
(flet ($e129 (bvugt ?e19 ?e50))
(flet ($e130 (bvsle ?e14 (zero_extend[3] ?e25)))
(flet ($e131 (bvule ?e55 (sign_extend[3] ?e64)))
(flet ($e132 (bvslt ?e56 ?e59))
(flet ($e133 (bvsgt ?e17 ?e13))
(flet ($e134 (bvsle (zero_extend[3] ?e61) ?e45))
(flet ($e135 (bvsge ?e44 (sign_extend[3] ?e62)))
(flet ($e136 (bvsle ?e40 ?e41))
(flet ($e137 (bvsgt ?e13 ?e40))
(flet ($e138 (bvsge ?e53 ?e45))
(flet ($e139 (bvugt ?e32 (zero_extend[3] ?e25)))
(flet ($e140 (distinct ?e57 ?e65))
(flet ($e141 (bvsgt v1 ?e3))
(flet ($e142 (distinct ?e9 ?e9))
(flet ($e143 (bvsle ?e62 ?e34))
(flet ($e144 (distinct ?e24 (sign_extend[3] ?e22)))
(flet ($e145 (bvsle ?e45 (sign_extend[3] ?e12)))
(flet ($e146 (bvslt ?e31 (sign_extend[3] ?e15)))
(flet ($e147 (bvult ?e29 ?e11))
(flet ($e148 (= ?e23 ?e62))
(flet ($e149 (bvsge ?e50 ?e17))
(flet ($e150 (bvugt (sign_extend[3] ?e63) ?e9))
(flet ($e151 (bvule ?e37 (sign_extend[3] ?e27)))
(flet ($e152 (bvule ?e65 ?e64))
(flet ($e153 (distinct ?e10 v1))
(flet ($e154 (distinct ?e24 ?e44))
(flet ($e155 (bvslt ?e60 ?e18))
(flet ($e156 (bvsle (sign_extend[3] ?e66) ?e6))
(flet ($e157 (bvugt ?e14 ?e28))
(flet ($e158 (bvule v1 ?e43))
(flet ($e159 (distinct ?e30 (sign_extend[3] ?e33)))
(flet ($e160 (bvult ?e46 ?e48))
(flet ($e161 (bvsle ?e36 ?e32))
(flet ($e162 (bvuge ?e9 ?e11))
(flet ($e163 (bvslt ?e34 ?e22))
(flet ($e164 (bvsle ?e55 (sign_extend[3] ?e41)))
(flet ($e165 (bvule ?e58 (sign_extend[3] ?e41)))
(flet ($e166 (bvsle ?e56 (zero_extend[3] ?e42)))
(flet ($e167 (bvslt ?e58 (sign_extend[3] ?e61)))
(flet ($e168 (distinct ?e34 ?e64))
(flet ($e169 (bvule ?e45 (zero_extend[3] ?e27)))
(flet ($e170 (bvult ?e35 ?e41))
(flet ($e171 (bvugt (sign_extend[3] ?e41) ?e37))
(flet ($e172 (= ?e4 ?e31))
(flet ($e173 (bvuge ?e28 ?e24))
(flet ($e174 (= ?e25 ?e21))
(flet ($e175 (bvsle ?e40 ?e57))
(flet ($e176 (bvule ?e26 (zero_extend[3] ?e47)))
(flet ($e177 (= ?e28 v0))
(flet ($e178 (bvult ?e44 (zero_extend[3] ?e20)))
(flet ($e179 (bvugt ?e59 (sign_extend[3] ?e23)))
(flet ($e180 (bvsgt ?e32 (zero_extend[3] ?e20)))
(flet ($e181 (bvult v0 ?e26))
(flet ($e182 (bvule ?e16 ?e56))
(flet ($e183 (bvuge ?e5 ?e36))
(flet ($e184 (bvsgt ?e33 ?e42))
(flet ($e185 (bvsge v2 (sign_extend[3] ?e12)))
(flet ($e186 (bvule ?e12 ?e7))
(flet ($e187 (bvsgt ?e59 ?e46))
(flet ($e188 (= ?e45 (zero_extend[3] ?e22)))
(flet ($e189 (bvule ?e10 ?e16))
(flet ($e190 (bvslt ?e51 (zero_extend[3] ?e66)))
(flet ($e191 (bvsle (sign_extend[3] ?e15) ?e37))
(flet ($e192 (bvsle (zero_extend[3] ?e63) ?e38))
(flet ($e193 (bvugt ?e43 ?e11))
(flet ($e194 (bvsgt (zero_extend[3] ?e17) ?e48))
(flet ($e195 (bvsgt ?e10 (zero_extend[3] ?e42)))
(flet ($e196 (bvsle ?e33 ?e20))
(flet ($e197 (bvslt ?e29 (zero_extend[3] ?e27)))
(flet ($e198 (distinct ?e53 ?e44))
(flet ($e199 (bvule ?e11 (zero_extend[3] ?e63)))
(flet ($e200 (bvsge ?e19 ?e47))
(flet ($e201 (= ?e17 ?e27))
(flet ($e202 (bvuge (zero_extend[3] ?e15) ?e43))
(flet ($e203 (= ?e10 (sign_extend[3] ?e60)))
(flet ($e204 (bvugt ?e43 (zero_extend[3] ?e57)))
(flet ($e205 (distinct ?e48 (zero_extend[3] ?e41)))
(flet ($e206 (bvsge ?e56 ?e53))
(flet ($e207 (bvsge (sign_extend[3] ?e23) ?e4))
(flet ($e208 (bvsle v0 ?e31))
(flet ($e209 (bvslt ?e28 (zero_extend[3] ?e27)))
(flet ($e210 (distinct (sign_extend[3] ?e41) ?e46))
(flet ($e211 (bvslt (sign_extend[3] ?e12) ?e38))
(flet ($e212 (bvsgt (zero_extend[3] ?e49) ?e39))
(flet ($e213 (bvsgt ?e31 (sign_extend[3] ?e62)))
(flet ($e214 (bvuge ?e40 ?e52))
(flet ($e215 (bvsle ?e44 (sign_extend[3] ?e65)))
(flet ($e216 (bvsle v0 (zero_extend[3] ?e13)))
(flet ($e217 (bvugt ?e35 ?e57))
(flet ($e218 (bvsgt (sign_extend[3] ?e64) ?e8))
(flet ($e219 (bvule (sign_extend[3] ?e41) ?e32))
(flet ($e220 (bvugt ?e56 ?e39))
(flet ($e221 (bvuge (zero_extend[3] ?e25) ?e38))
(flet ($e222 (bvuge (sign_extend[3] ?e57) ?e36))
(flet ($e223 (bvsge ?e27 ?e7))
(flet ($e224 (bvuge ?e66 ?e15))
(flet ($e225 (bvuge ?e56 (zero_extend[3] ?e63)))
(flet ($e226 (bvuge ?e4 ?e36))
(flet ($e227 (bvugt ?e37 ?e9))
(flet ($e228 (bvule ?e44 (sign_extend[3] ?e61)))
(flet ($e229 (= ?e19 ?e47))
(flet ($e230 (bvuge ?e28 (zero_extend[3] ?e25)))
(flet ($e231 (bvsgt ?e32 (zero_extend[3] ?e18)))
(flet ($e232 (bvuge ?e57 ?e57))
(flet ($e233 (bvuge v2 ?e38))
(flet ($e234 (bvuge ?e15 ?e57))
(flet ($e235 (bvuge ?e58 v2))
(flet ($e236 (bvuge ?e4 ?e43))
(flet ($e237 (bvsle v0 (sign_extend[3] ?e19)))
(flet ($e238 (bvslt (zero_extend[3] ?e20) ?e51))
(flet ($e239 (= ?e58 (sign_extend[3] ?e49)))
(flet ($e240 (bvult ?e5 (zero_extend[3] ?e33)))
(flet ($e241 (bvugt ?e42 ?e61))
(flet ($e242 (bvugt ?e46 v1))
(flet ($e243 (= ?e30 (zero_extend[3] ?e15)))
(flet ($e244 (bvult ?e36 (sign_extend[3] ?e61)))
(flet ($e245 (bvsle ?e62 ?e65))
(flet ($e246 (bvsgt ?e10 (zero_extend[3] ?e65)))
(flet ($e247 (bvule ?e16 (sign_extend[3] ?e66)))
(flet ($e248 (= ?e14 ?e44))
(flet ($e249 (bvule ?e30 ?e58))
(flet ($e250 (bvslt (zero_extend[3] ?e42) ?e48))
(flet ($e251 (bvsle (sign_extend[3] ?e35) ?e31))
(flet ($e252 (bvugt (sign_extend[3] ?e54) ?e4))
(flet ($e253 
(and
 (or $e183 $e232 (not $e143))
 (or $e127 (not $e74) $e73)
 (or (not $e112) (not $e81) $e71)
 (or $e245 $e180 $e130)
 (or $e115 (not $e249) (not $e82))
 (or $e99 (not $e177) (not $e182))
 (or (not $e243) (not $e183) (not $e79))
 (or (not $e150) (not $e171) $e161)
 (or (not $e91) $e105 $e129)
 (or (not $e187) $e119 $e107)
 (or (not $e166) (not $e74) $e209)
 (or (not $e203) (not $e69) (not $e143))
 (or $e163 $e210 $e192)
 (or $e188 $e207 (not $e222))
 (or $e117 $e222 $e196)
 (or (not $e90) (not $e83) $e150)
 (or (not $e227) (not $e211) (not $e235))
 (or $e82 $e146 (not $e96))
 (or $e72 (not $e108) $e103)
 (or (not $e115) (not $e74) $e215)
 (or (not $e234) (not $e241) $e163)
 (or (not $e173) (not $e154) $e73)
 (or (not $e228) $e113 $e77)
 (or (not $e93) $e226 (not $e194))
 (or $e243 (not $e157) (not $e126))
 (or $e242 $e79 (not $e92))
 (or $e168 (not $e94) $e145)
 (or (not $e167) $e200 (not $e100))
 (or (not $e221) $e188 $e217)
 (or $e106 (not $e87) (not $e203))
 (or (not $e243) (not $e166) $e172)
 (or $e82 $e215 (not $e124))
 (or (not $e137) (not $e136) (not $e209))
 (or $e135 (not $e222) (not $e182))
 (or $e144 (not $e224) (not $e163))
 (or (not $e237) (not $e89) $e206)
 (or (not $e217) (not $e88) $e77)
 (or $e165 $e76 (not $e246))
 (or $e192 $e158 $e115)
 (or $e242 (not $e202) (not $e196))
 (or $e130 $e231 $e88)
 (or $e78 $e213 (not $e189))
 (or (not $e170) (not $e146) (not $e154))
 (or $e170 $e162 (not $e177))
 (or $e128 (not $e76) (not $e161))
 (or $e167 (not $e169) $e212)
 (or (not $e103) (not $e148) (not $e215))
 (or $e210 (not $e198) (not $e168))
 (or $e73 $e195 $e203)
 (or (not $e190) $e139 $e227)
 (or $e226 (not $e123) $e206)
 (or (not $e228) (not $e248) $e211)
 (or (not $e85) $e200 $e198)
 (or $e233 (not $e172) (not $e250))
 (or $e141 $e123 (not $e129))
 (or (not $e129) (not $e126) $e249)
 (or $e247 (not $e174) $e243)
 (or $e100 (not $e191) (not $e242))
 (or (not $e205) (not $e189) $e82)
 (or $e204 $e127 (not $e251))
 (or $e95 (not $e121) (not $e136))
 (or (not $e163) $e204 $e98)
 (or $e153 $e167 $e212)
 (or (not $e95) $e251 $e168)
 (or $e192 (not $e236) (not $e145))
 (or (not $e125) (not $e240) $e69)
 (or (not $e148) (not $e251) (not $e85))
 (or $e143 (not $e252) (not $e216))
 (or $e233 (not $e204) $e96)
 (or $e126 $e68 (not $e69))
 (or (not $e251) (not $e209) $e238)
 (or $e248 (not $e114) $e228)
 (or $e78 $e239 $e200)
 (or (not $e201) (not $e108) (not $e118))
 (or (not $e234) $e249 $e252)
 (or $e113 (not $e108) $e184)
 (or $e77 $e149 $e226)
 (or $e166 $e218 $e183)
 (or $e135 $e101 $e184)
 (or (not $e156) (not $e218) (not $e97))
 (or $e88 (not $e180) $e191)
 (or (not $e127) (not $e170) $e97)
 (or $e204 (not $e220) $e154)
 (or $e214 $e181 $e250)
 (or (not $e105) $e89 $e111)
 (or (not $e95) (not $e206) (not $e119))
 (or $e224 (not $e232) (not $e244))
 (or $e228 $e219 (not $e250))
 (or (not $e172) $e97 $e142)
 (or (not $e129) $e112 $e144)
 (or (not $e171) $e78 (not $e136))
 (or (not $e230) $e225 (not $e236))
 (or $e101 $e68 $e155)
))
$e253
))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))


from FAdo.fa import NFA, DFA,Epsilon
nfa = NFA()
nfa.addInitial(2)
nfa.addFinal(133)
nfa.addFinal(134)
nfa.addState(0)
nfa.addState(1)
nfa.addTransition(1,Epsilon , 1)
nfa.addTransition(1,Epsilon , 5)
nfa.addState(2)
nfa.addTransition(2,Epsilon , 1)
nfa.addTransition(2,Epsilon , 5)
nfa.addState(3)
nfa.addState(4)
nfa.addTransition(4,Epsilon , 4)
nfa.addTransition(4,Epsilon , 128)
nfa.addState(5)
nfa.addTransition(5,Epsilon , 4)
nfa.addTransition(5,Epsilon , 128)
nfa.addState(6)
nfa.addTransition(6, 2, 8)
nfa.addTransition(6, 3, 7)
nfa.addTransition(6, 6, 7)
nfa.addState(7)
nfa.addTransition(7,Epsilon , 131)
nfa.addTransition(7, 8, 6)
nfa.addState(8)
nfa.addTransition(8, 2, 8)
nfa.addState(128)
nfa.addTransition(128,Epsilon , 6)
nfa.addTransition(128,Epsilon , 10)
nfa.addTransition(128,Epsilon , 115)
nfa.addState(9)
nfa.addTransition(9,Epsilon , 13)
nfa.addState(10)
nfa.addTransition(10, 4, 9)
nfa.addState(11)
nfa.addState(12)
nfa.addTransition(12,Epsilon , 12)
nfa.addTransition(12,Epsilon , 56)
nfa.addState(13)
nfa.addTransition(13,Epsilon , 12)
nfa.addTransition(13,Epsilon , 56)
nfa.addState(14)
nfa.addTransition(14, 2, 16)
nfa.addTransition(14, 3, 15)
nfa.addTransition(14, 6, 15)
nfa.addState(15)
nfa.addTransition(15,Epsilon , 59)
nfa.addTransition(15, 8, 14)
nfa.addState(16)
nfa.addTransition(16, 2, 16)
nfa.addState(56)
nfa.addTransition(56,Epsilon , 14)
nfa.addTransition(56,Epsilon , 18)
nfa.addTransition(56,Epsilon , 43)
nfa.addState(17)
nfa.addTransition(17,Epsilon , 21)
nfa.addState(18)
nfa.addTransition(18, 4, 17)
nfa.addState(19)
nfa.addState(20)
nfa.addTransition(20,Epsilon , 20)
nfa.addTransition(20,Epsilon , 22)
nfa.addState(21)
nfa.addTransition(21,Epsilon , 20)
nfa.addTransition(21,Epsilon , 22)
nfa.addState(22)
nfa.addTransition(22, 2, 24)
nfa.addTransition(22, 3, 23)
nfa.addTransition(22, 6, 23)
nfa.addState(23)
nfa.addTransition(23,Epsilon , 27)
nfa.addTransition(23, 8, 22)
nfa.addState(24)
nfa.addTransition(24, 2, 24)
nfa.addState(25)
nfa.addState(26)
nfa.addTransition(26,Epsilon , 26)
nfa.addTransition(26,Epsilon , 28)
nfa.addState(27)
nfa.addTransition(27,Epsilon , 26)
nfa.addTransition(27,Epsilon , 28)
nfa.addState(28)
nfa.addTransition(28,Epsilon , 32)
nfa.addState(29)
nfa.addTransition(29, 0, 28)
nfa.addTransition(29, 5, 28)
nfa.addTransition(29, 8, 28)
nfa.addState(30)
nfa.addState(31)
nfa.addTransition(31,Epsilon , 31)
nfa.addTransition(31,Epsilon , 33)
nfa.addState(32)
nfa.addTransition(32,Epsilon , 31)
nfa.addTransition(32,Epsilon , 33)
nfa.addState(33)
nfa.addTransition(33, 2, 35)
nfa.addTransition(33, 3, 34)
nfa.addTransition(33, 6, 34)
nfa.addState(34)
nfa.addTransition(34,Epsilon , 38)
nfa.addTransition(34, 8, 33)
nfa.addState(35)
nfa.addTransition(35, 2, 35)
nfa.addState(36)
nfa.addState(37)
nfa.addTransition(37,Epsilon , 37)
nfa.addTransition(37,Epsilon , 41)
nfa.addState(38)
nfa.addTransition(38,Epsilon , 37)
nfa.addTransition(38,Epsilon , 41)
nfa.addTransition(38,Epsilon , 59)
nfa.addState(39)
nfa.addState(40)
nfa.addTransition(40,Epsilon , 59)
nfa.addTransition(40, 0, 39)
nfa.addState(41)
nfa.addTransition(41, 0, 39)
nfa.addTransition(41, 1, 39)
nfa.addTransition(41, 5, 39)
nfa.addTransition(41, 8, 40)
nfa.addState(42)
nfa.addTransition(42,Epsilon , 46)
nfa.addState(43)
nfa.addTransition(43, 4, 42)
nfa.addState(44)
nfa.addState(45)
nfa.addTransition(45,Epsilon , 45)
nfa.addTransition(45,Epsilon , 47)
nfa.addState(46)
nfa.addTransition(46,Epsilon , 45)
nfa.addTransition(46,Epsilon , 47)
nfa.addState(47)
nfa.addTransition(47, 2, 49)
nfa.addTransition(47, 3, 48)
nfa.addTransition(47, 6, 48)
nfa.addState(48)
nfa.addTransition(48,Epsilon , 52)
nfa.addTransition(48, 8, 47)
nfa.addState(49)
nfa.addTransition(49, 2, 49)
nfa.addState(50)
nfa.addState(51)
nfa.addTransition(51,Epsilon , 51)
nfa.addTransition(51,Epsilon , 46)
nfa.addTransition(51,Epsilon , 55)
nfa.addState(52)
nfa.addTransition(52,Epsilon , 51)
nfa.addTransition(52,Epsilon , 46)
nfa.addTransition(52,Epsilon , 55)
nfa.addTransition(52,Epsilon , 59)
nfa.addState(53)
nfa.addState(54)
nfa.addTransition(54,Epsilon , 59)
nfa.addTransition(54, 0, 53)
nfa.addState(55)
nfa.addTransition(55, 0, 53)
nfa.addTransition(55, 1, 53)
nfa.addTransition(55, 5, 53)
nfa.addTransition(55, 8, 54)
nfa.addState(57)
nfa.addState(58)
nfa.addTransition(58,Epsilon , 58)
nfa.addTransition(58,Epsilon , 60)
nfa.addState(59)
nfa.addTransition(59,Epsilon , 58)
nfa.addTransition(59,Epsilon , 60)
nfa.addState(60)
nfa.addTransition(60,Epsilon , 64)
nfa.addState(61)
nfa.addTransition(61, 0, 60)
nfa.addTransition(61, 5, 60)
nfa.addTransition(61, 8, 60)
nfa.addState(62)
nfa.addState(63)
nfa.addTransition(63,Epsilon , 63)
nfa.addTransition(63,Epsilon , 107)
nfa.addState(64)
nfa.addTransition(64,Epsilon , 63)
nfa.addTransition(64,Epsilon , 107)
nfa.addState(65)
nfa.addTransition(65, 2, 67)
nfa.addTransition(65, 3, 66)
nfa.addTransition(65, 6, 66)
nfa.addState(66)
nfa.addTransition(66,Epsilon , 110)
nfa.addTransition(66, 8, 65)
nfa.addState(67)
nfa.addTransition(67, 2, 67)
nfa.addState(107)
nfa.addTransition(107,Epsilon , 65)
nfa.addTransition(107,Epsilon , 69)
nfa.addTransition(107,Epsilon , 94)
nfa.addState(68)
nfa.addTransition(68,Epsilon , 72)
nfa.addState(69)
nfa.addTransition(69, 4, 68)
nfa.addState(70)
nfa.addState(71)
nfa.addTransition(71,Epsilon , 71)
nfa.addTransition(71,Epsilon , 73)
nfa.addState(72)
nfa.addTransition(72,Epsilon , 71)
nfa.addTransition(72,Epsilon , 73)
nfa.addState(73)
nfa.addTransition(73, 2, 75)
nfa.addTransition(73, 3, 74)
nfa.addTransition(73, 6, 74)
nfa.addState(74)
nfa.addTransition(74,Epsilon , 78)
nfa.addTransition(74, 8, 73)
nfa.addState(75)
nfa.addTransition(75, 2, 75)
nfa.addState(76)
nfa.addState(77)
nfa.addTransition(77,Epsilon , 77)
nfa.addTransition(77,Epsilon , 79)
nfa.addState(78)
nfa.addTransition(78,Epsilon , 77)
nfa.addTransition(78,Epsilon , 79)
nfa.addState(79)
nfa.addTransition(79,Epsilon , 83)
nfa.addState(80)
nfa.addTransition(80, 0, 79)
nfa.addTransition(80, 5, 79)
nfa.addTransition(80, 8, 79)
nfa.addState(81)
nfa.addState(82)
nfa.addTransition(82,Epsilon , 82)
nfa.addTransition(82,Epsilon , 84)
nfa.addState(83)
nfa.addTransition(83,Epsilon , 82)
nfa.addTransition(83,Epsilon , 84)
nfa.addState(84)
nfa.addTransition(84, 2, 86)
nfa.addTransition(84, 3, 85)
nfa.addTransition(84, 6, 85)
nfa.addState(85)
nfa.addTransition(85,Epsilon , 89)
nfa.addTransition(85, 8, 84)
nfa.addState(86)
nfa.addTransition(86, 2, 86)
nfa.addState(87)
nfa.addState(88)
nfa.addTransition(88,Epsilon , 88)
nfa.addTransition(88,Epsilon , 92)
nfa.addState(89)
nfa.addTransition(89,Epsilon , 88)
nfa.addTransition(89,Epsilon , 92)
nfa.addTransition(89,Epsilon , 110)
nfa.addState(90)
nfa.addState(91)
nfa.addTransition(91,Epsilon , 110)
nfa.addTransition(91, 0, 90)
nfa.addState(92)
nfa.addTransition(92, 0, 90)
nfa.addTransition(92, 1, 90)
nfa.addTransition(92, 5, 90)
nfa.addTransition(92, 8, 91)
nfa.addState(93)
nfa.addTransition(93,Epsilon , 97)
nfa.addState(94)
nfa.addTransition(94, 4, 93)
nfa.addState(95)
nfa.addState(96)
nfa.addTransition(96,Epsilon , 96)
nfa.addTransition(96,Epsilon , 98)
nfa.addState(97)
nfa.addTransition(97,Epsilon , 96)
nfa.addTransition(97,Epsilon , 98)
nfa.addState(98)
nfa.addTransition(98, 2, 100)
nfa.addTransition(98, 3, 99)
nfa.addTransition(98, 6, 99)
nfa.addState(99)
nfa.addTransition(99,Epsilon , 103)
nfa.addTransition(99, 8, 98)
nfa.addState(100)
nfa.addTransition(100, 2, 100)
nfa.addState(101)
nfa.addState(102)
nfa.addTransition(102,Epsilon , 102)
nfa.addTransition(102,Epsilon , 97)
nfa.addTransition(102,Epsilon , 106)
nfa.addState(103)
nfa.addTransition(103,Epsilon , 102)
nfa.addTransition(103,Epsilon , 97)
nfa.addTransition(103,Epsilon , 106)
nfa.addTransition(103,Epsilon , 110)
nfa.addState(104)
nfa.addState(105)
nfa.addTransition(105,Epsilon , 110)
nfa.addTransition(105, 0, 104)
nfa.addState(106)
nfa.addTransition(106, 0, 104)
nfa.addTransition(106, 1, 104)
nfa.addTransition(106, 5, 104)
nfa.addTransition(106, 8, 105)
nfa.addState(108)
nfa.addState(109)
nfa.addTransition(109,Epsilon , 109)
nfa.addTransition(109,Epsilon , 113)
nfa.addState(110)
nfa.addTransition(110,Epsilon , 109)
nfa.addTransition(110,Epsilon , 113)
nfa.addTransition(110,Epsilon , 131)
nfa.addState(111)
nfa.addState(112)
nfa.addTransition(112,Epsilon , 131)
nfa.addTransition(112, 0, 111)
nfa.addState(113)
nfa.addTransition(113, 0, 111)
nfa.addTransition(113, 1, 111)
nfa.addTransition(113, 5, 111)
nfa.addTransition(113, 8, 112)
nfa.addState(114)
nfa.addTransition(114,Epsilon , 118)
nfa.addState(115)
nfa.addTransition(115, 4, 114)
nfa.addState(116)
nfa.addState(117)
nfa.addTransition(117,Epsilon , 117)
nfa.addTransition(117,Epsilon , 119)
nfa.addState(118)
nfa.addTransition(118,Epsilon , 117)
nfa.addTransition(118,Epsilon , 119)
nfa.addState(119)
nfa.addTransition(119, 2, 121)
nfa.addTransition(119, 3, 120)
nfa.addTransition(119, 6, 120)
nfa.addState(120)
nfa.addTransition(120,Epsilon , 124)
nfa.addTransition(120, 8, 119)
nfa.addState(121)
nfa.addTransition(121, 2, 121)
nfa.addState(122)
nfa.addState(123)
nfa.addTransition(123,Epsilon , 123)
nfa.addTransition(123,Epsilon , 118)
nfa.addTransition(123,Epsilon , 127)
nfa.addState(124)
nfa.addTransition(124,Epsilon , 123)
nfa.addTransition(124,Epsilon , 118)
nfa.addTransition(124,Epsilon , 127)
nfa.addTransition(124,Epsilon , 131)
nfa.addState(125)
nfa.addState(126)
nfa.addTransition(126,Epsilon , 131)
nfa.addTransition(126, 0, 125)
nfa.addState(127)
nfa.addTransition(127, 0, 125)
nfa.addTransition(127, 1, 125)
nfa.addTransition(127, 5, 125)
nfa.addTransition(127, 8, 126)
nfa.addState(129)
nfa.addState(130)
nfa.addTransition(130,Epsilon , 130)
nfa.addTransition(130,Epsilon , 134)
nfa.addState(131)
nfa.addTransition(131,Epsilon , 130)
nfa.addTransition(131,Epsilon , 134)
nfa.addState(132)
nfa.addState(133)
nfa.addTransition(133,Epsilon , 133)
nfa.addTransition(133,Epsilon , 5)
nfa.addState(134)
nfa.addTransition(134,Epsilon , 133)
nfa.addTransition(134,Epsilon , 5)
dfa = nfa.elimEpsilon()
trim = nfa.trim()
dfa = trim.toDFA()
print(dfa.Initial)
print(len(dfa.Final))
for x in dfa.Final:
    print(x)

transitions = nfa.transitions()
states = nfa.States
symbols = set()
for transition in transitions:
    symbols.add(transition[1])
    state_from = transition[0]
    symbol = transition[1]
    state_to = transition[2]
    print(state_from, symbol, state_to)

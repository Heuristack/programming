\version "2.18.2"

#(set-global-staff-size 22)
versiondate = #(strftime "Version %Y%m%d" (localtime (current-time)))

\paper {
  top-margin = #10
  indent = #0
}
\header {
  title = "Music Notes"
  subtitle = "concise expression of music theory for recapping"
  poet = "Mnemonics"
  composer = "Lance Li"
  meter = ""
  arranger = ""
  tagline = \versiondate
}

\absolute
{
  \clef treble
  \time 3/4
  \bar ".|"
  <a c' e'>
  <a' c'' e''>
  <a'' c''' e'''>
  <b d'>
  <b' d''>
  <b'' d'''>
  <g f'>
  <g' f''>
  <g'' f'''>
  \bar "."
  <a c' e'>
  <b d'>
  <g f'>
  <a' c'' e''>
  <b' d''>
  <g' f''>
  <a'' c''' e'''>
  <b'' d'''>
  <g'' f'''>
  \bar "|."
}
\absolute
{
  \clef bass
  \time 3/4
  \bar ".|"
  <a,, c, e,>
  <a, c e>
  <a c' e'>
  <b,, d,>
  <b, d>
  <b d'>
  <g,, f,>
  <g, f>
  <g f'>
  \bar "."
  <a,, c, e,>
  <b,, d,>
  <g,, f,>
  <a, c e>
  <b, d>
  <g, f>
  <a c' e'>
  <b d'>
  <g f'>
  \bar "|."
}
\markup{Notes on Clef: ACE-BD-GF, [F]G-A[B]C[D]E-F[G]}

\markup
{
  Num(Notes) = 7, Num(Fingers) = 5,
  AB-CDEFG-AB,ABCDEFG,CDEFGAB,
  FG-ABCDE-FG
}

\markup
{
  2nd Notes Sequence:
  ACEG-BDF,FACE-GBD,FACEG,BD-FACEG-BD
}

\markup
{
  Reverse(ABCDEFG)=GFEDCBA,
  Reverse(CDEFGAB)=BAGFEDC
}

\markup
{
  Chord Vocabulary: ACE,BDF,CDG,DFA,EGB,FAC,GBD
}

\markup
{
  Num(Lines) = 5, Num(Spaces) = 4,
  Num(Notes) = 3 Lines + 4 Spaces = 4 Lines + 3 Spaces
}

\markup
{
  Cleff:
  Lowest Line = Uppest Space,
  Lowest Space = Uppest Line
}

\markup
{
  Middle-C: C4, 
  (C1)-C2-C3-[C4]-C5-C6-(C7),
  A-C-E,F-C-G,B-C-D
}

\markup
{
  Tetrachords: 4 Notes = 3 Steps, W: Whole Step, H: Half-Step,
  Major Scale: WWH-W-WWH
}

\markup
{
  Num(W) = 7 * 7 + 3 = 52,
  Num(B) = 5 * 7 + 1 = 36,
  Num(K) = Num(W) + Num(B) = 52 + 36 = 88
}

\markup
{
  Scales: F-C-G (Middle-C position LH-RH),
  Major Scales: C,G,F,
  Minor Scales: A,E,D
}

\markup
{
  Minor: right next to a hand of major
  Major Note + 5 = Minor Note,
  Major Note - 2 = Minor Note
}

\markup
{
  5th Notes Sequence:
  F-C-G-D-A-E-B
}

\markup
{
  Chords: Note(1),Note(3),Note(5),Note(7),1-3-5,1-3-7,
  Primary Chords: I, IV, V7,
}

\markup
{
  Chord(I) = root, Chord(V) = Note(4)+Num(Fingers)-1=Note(8)=Octave(root), Chord(V7) = Finger(5)
}

\markup
{
  Chord(I)-Chord(IV) = Right-Shift on Finger(5),
  Chord(IV)-Chord(V7) = Left-Shift on Finter(2)
}



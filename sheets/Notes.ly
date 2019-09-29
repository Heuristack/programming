\version "2.18.2"

#(set-global-staff-size 22)

\paper {
  top-margin = #10
  indent = #10
}
\header {
  title = ""
  subtitle = ""
  poet = ""
  composer = ""
  meter = ""
  arranger = ""
  tagline = "ACE-BD-GF Version 20190926"
}

\markup{Notes on Clef: ACE-BD-GF, [F]G-A[B]C[D]E-F[G]}
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
  Middle C: C4, (C1)-C2-C3-[C4]-C5-C6-(C7)
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
  F-C-G,
  Major Scales: C,G,F,
  Minor Scales: A,E,D
}

\markup
{
  Minor Note: The note right next to the hand of major note
}

\markup
{
  Major Note + 5 = Minor Note,
  Major Note - 2 = Minor Note
}

\markup
{
  5th Notes Sequence:
  F-C-G-D-A-E-B
}


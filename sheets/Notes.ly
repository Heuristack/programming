\version "2.18.2"

#(set-global-staff-size 22)

\paper {
  top-margin = #15
  indent = #20
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

\markup{ACE-BD-GF}
\absolute {
  \clef treble
  \time 3/4
  \bar "."
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
  \bar "."
}
\absolute {
  \clef bass
  \time 3/4
  \bar "."
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
  \bar "."
}


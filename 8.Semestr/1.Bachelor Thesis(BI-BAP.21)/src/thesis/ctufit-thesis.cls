%% This is the ctufit-thesis document class. It is used to produce theses
%% for submission to Czech Technical University, Faculty of Information Technology.
%%
%% Get the newest version from
%% https://gitlab.fit.cvut.cz/theses-templates/FITthesis-LaTeX
%%
%%
%% Copyright 2024, Tomas Novacek
%% Copyright 2021, Eliska Sestakova and Ondrej Guth
%%
%% This work may be distributed and/or modified under the
%% conditions of the LaTeX Project Public License, either version 1.3
%% of this license or (at your option) any later version.
%% The latest version of this license is in
%%  https://www.latex-project.org/lppl.txt
%% and version 1.3 or later is part of all distributions of LaTeX
%% version 2005/12/01 or later.
%%
%% This work has the LPPL maintenance status `maintained'.
%%
%% The current maintainer of this work is Tomas Novacek.
%% Alternatively, submit bug reports to the tracker at
%% https://gitlab.fit.cvut.cz/theses-templates/FITthesis-LaTeX/issues
%%
%%

% identification

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ctufit-thesis}[2021/08/06 CTU FIT thesis template]

% preliminary declarations

% options
\DeclareOption{bachelor}{\def\@ctufitthesistype{B}}
\DeclareOption{master}{\def\@ctufitthesistype{M}}
\DeclareOption{dissertation}{\def\@ctufitthesistype{D}}
\DeclareOption{bw}{\def\@ctufitthesisblackandwhite}
\DeclareOption{czech}{
	\AtBeginDocument{\selectlanguage{czech}}
	\PassOptionsToPackage{english,main=czech}{babel}
	\def\@ctufitlang{C}
}
\DeclareOption{english}{
	\AtBeginDocument{\selectlanguage{english}}
	\PassOptionsToPackage{czech,main=english}{babel}
	\def\@ctufitlang{E}
}
\DeclareOption{slovak}{
	\AtBeginDocument{\selectlanguage{slovak}}
	\PassOptionsToPackage{english,main=slovak}{babel}
	\def\@ctufitlang{S}
}
\DeclareOption{subsubsection}{
	\def\@ctufitsecdepth{3}
}
\DeclareOption{paragraph}{
	\def\@ctufitsecdepth{4}
}
\PassOptionsToPackage{svgnames}{xcolor}
\PassOptionsToPackage{newfloat}{minted}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{book}}
\ExecuteOptions{unicode}
\ExecuteOptions{subsubsection}
\ProcessOptions\relax

% main declarations, loading files
\LoadClass[a4paper,11pt]{book}[2020/04/10]
\RequirePackage{xcolor}[2023/11/15]
\RequirePackage[a-1b]{pdfx}  % PDF/A-1b compliance
\RequirePackage{babel}[2021/03/03]
\if@twoside
    \RequirePackage[top=4.6cm,bottom=4cm,footskip=4em,inner=4.7cm,outer=3.25cm]{geometry}[2020/01/02] %page layout
\else
    \RequirePackage[left=3.95cm,right=4.0cm,top=4.6cm,bottom=4cm,footskip=4em]{geometry}[2020/01/02] %page layout
\fi
\RequirePackage{setspace}[2011/12/19] %line spacing in title page
\RequirePackage[labelsep=space,singlelinecheck=false,font={up,small},labelfont={sf,bf}]{caption}[2020/05/30]
\RequirePackage{fancyhdr}[2019/01/31]
\RequirePackage{multicol}[2019/12/09] % summary page
\RequirePackage{titlesec}[2019/10/16]

\ifdefined\@ctufitthesisblackandwhite
	\definecolor{decoration}{RGB}{0, 0, 0} %CTU blue
	\definecolor{heading}{RGB}{0, 0, 0}
	\definecolor{headbackgroundgray}{RGB}{208, 208, 208} %light blue
	\definecolor{backgroundgray}{RGB}{240, 240, 240} %CTU light blue
	\definecolor{headgray}{rgb}{0.50,0.50,0.50}
	\definecolor{enumgray}{RGB}{0, 0, 0} %CTU blue
\else
	\definecolor{decoration}{RGB}{0, 122, 195} %CTU blue
	\definecolor{heading}{RGB}{0, 122, 195}
	\definecolor{headbackgroundgray}{RGB}{199, 219, 241} %light blue
	\definecolor{backgroundgray}{RGB}{199, 219, 241} %CTU light blue
	\definecolor{headgray}{rgb}{0.50,0.50,0.51}
	\definecolor{enumgray}{RGB}{0, 122, 195} %CTU blue
\fi
% colours end

\RequirePackage{hyperref}[2020/05/15]

\DeclareRobustCommand{\ctufittitle}[1]{
	\def\thectufittitle{#1}
	\title{#1}
}
\DeclareRobustCommand{\ctufitauthorfull}[1]{
	\def\thectufitauthorfull{#1}
	\author{#1}
}
\DeclareRobustCommand{\ctufitauthorsurnames}[1]{
	\def\thectufitauthorsurnames{#1}
	\author{#1}
}
\DeclareRobustCommand{\ctufitauthorgivennames}[1]{
	\def\thectufitauthorgivennames{#1}
	\author{#1}
}
\DeclareRobustCommand{\ctufitsupervisor}[1]{
	\def\thectufitsupervisor{#1}
}
\DeclareRobustCommand{\ctufitdepartment}[1]{
	\def\thectufitdepartment{#1}
}
\DeclareRobustCommand{\ctufityear}[1]{
	\def\thectufityear{#1}
	\date{#1}
}
\DeclareRobustCommand{\ctufitdeclarationplace}[1]{
	\def\thectufitdeclarationplace{#1}
}
\DeclareRobustCommand{\ctufitdeclarationdate}[1]{
	\def\thectufitdeclarationdate{#1}
}
\DeclareRobustCommand{\ctufitabstractCZE}[1]{
	\def\thectufitabstrakt{#1}
}
\DeclareRobustCommand{\ctufitabstractENG}[1]{
	\def\thectufitabstract{#1}
}
\DeclareRobustCommand{\ctufitkeywordsCZE}[1]{
	\def\thectufitklicovaslova{#1}
}
\DeclareRobustCommand{\ctufitkeywordsENG}[1]{
	\def\thectufitkeywords{#1}
}
\DeclareRobustCommand{\thectufitthesistype}{%
	\if\@ctufitthesistype B{%
		\if\@ctufitlang C{Bakal{\' a}{\v r}sk{\' a} pr{\' a}ce}\else\if\@ctufitlang S{Bakal{\' a}rska pr{\' a}ca}\else{Bachelor's thesis}\fi\fi
	}\else\if\@ctufitthesistype M{%
		\if\@ctufitlang C{Diplomov{\' a} pr{\' a}ce}\else\if\@ctufitlang S{Diplomov{\' a} pr{\' a}ca}\else{Master's thesis}\fi\fi
	}\else\if\@ctufitthesistype D{Dissertation thesis}\else{\ClassError{ctufit-thesis}{Thesis type not specified}{Add either `bachelor', `master', or `dissertation' option to this document class}}\fi\fi\fi
}

\DeclareRobustCommand{\thectufituniversity}{\if\@ctufitlang C{{\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze}\else\if\@ctufitlang S{{\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze}\else{Czech Technical University in Prague}\fi\fi}

\DeclareRobustCommand{\thectufitfaculty}{\if\@ctufitlang C{Fakulta informa{\v c}n{\' i}ch technologi{\' i}}\else\if\@ctufitlang S{Fakulta informa{\v c}n{\' i}ch technologi{\' i}}\else{Faculty of Information Technology}\fi\fi}

\DeclareRobustCommand{\thectufitsupervisorlabelcapital}{\if\@ctufitlang C{Vedouc{\' i}}\else\if\@ctufitlang S{Ved\'uci}\else{Supervisor}\fi\fi}

\DeclareRobustCommand{\thectufitcitationlabel}{\if\@ctufitlang C{Odkaz na tuto pr{\' a}ci}\else\if\@ctufitlang S{Odkaz na t\'uto pr{\' a}cu}\else{Citation of this thesis}\fi\fi}

\DeclareRobustCommand{\thectufitallrightsreservedlabel}{\if\@ctufitlang C{V{\v s}echna pr{\' a}va vyhrazena.}\else\if\@ctufitlang S{V{\v s}etky pr{\' a}va vyhraden\'e.}\else{All rights reserved.}\fi\fi}

\DeclareRobustCommand{\thectufitlistinglabel}{\if\@ctufitlang C{V{\'y}pis k{\'o}du}\else\if\@ctufitlang S{V{\'y}pis k{\'o}du}\else{Code listing}\fi\fi}

\DeclareRobustCommand{\thectufitlollabel}{\if\@ctufitlang C{Seznam v{\'y}pis{\r u} k{\'o}du}\else\if\@ctufitlang S{Zoznam v{\'y}pisov k{\'o}du}\else{List of code listings}\fi\fi}

\DeclareRobustCommand{\thectufitdeclarationlabel}{\if\@ctufitlang C{Prohlášení}\else\if\@ctufitlang E{Declaration}\else{Vyhlásenie}\fi\fi}

\DeclareRobustCommand{\thectufitabbreviationlabel}{\if\@ctufitlang C{Seznam zkratek}\else\if\@ctufitlang E{List of abbreviations}\else{Zoznam skratiek}\fi\fi}

\DeclareRobustCommand{\thectufitcopyrighttext}{\if\@ctufitlang C{Tato pr{\' a}ce vznikla jako {\v s}koln{\' i} d{\' i}lo na {\v C}esk{\' e}m vysok{\' e}m u{\v c}en{\' i} technick{\' e}m v~Praze, Fakult{\v e} informa{\v c}n{\' i}ch technologi{\' i}. Pr{\' a}ce je chr{\' a}n{\v e}na pr{\' a}vn{\' i}mi p{\v r}edpisy a~mezin{\' a}rodn{\' i}mi {\' u}mluvami o~pr{\' a}vu autorsk{\' e}m a~pr{\' a}vech souvisej{\' i}c{\' i}ch s~pr{\' a}vem autorsk{\' y}m. K~jej\'\i{}mu u\v zit\'\i{}, s~v\'yjimkou bez\'uplatn\'ych z\'akonn\'ych licenc\'\i{} a nad r\'amec opr\'avn\v en\'\i{} uveden\'ych v~Prohl\'a\v sen\'\i{}, je nezbytn\'y souhlas autora.}\else\if\@ctufitlang S{T\'ato pr\'aca vznikla ako \v skolsk\'e dielo na  FIT \v CVUT v Prahe. Pr\'aca je chr\'anen\'a medzin\'arodn\'ymi predpismi a~zmluvami o~autorskom pr\'ave a~pr\'avach s\'uvisiacich s~autorsk\'ym pr\'avom. Na jej vyu\v zitie, s~v\'ynimkou bezplatn\'ych z\'akonn\'ych licenci\'\i, je nutn\'y s\'uhlas autora.}\else{This thesis is school work as defined by Copyright Act of the Czech Republic. It has been submitted at Czech Technical University in Prague, Faculty of Information Technology. The thesis is protected by the Copyright Act and its usage without author's permission is prohibited (with exceptions defined by the Copyright Act).}\fi\fi}

% title page
\renewcommand{\maketitle}{\begin{titlepage}%
\newgeometry{left=67mm,top=80mm,right=40mm}%\thispagestyle{empty}%
\noindent{\large\noindent\thectufitthesistype}
\vskip 3mm
\noindent{\noindent\huge\bfseries\color{black}\begin{flushleft}\begin{onehalfspace}\MakeUppercase{\thectufittitle}\end{onehalfspace}\end{flushleft}}
\vskip 35mm
\noindent{\large  \bfseries \thectufitauthorfull}

\vfill

\noindent{\thectufitfaculty\\
\thectufitdepartment\\
\thectufitsupervisorlabelcapital: \thectufitsupervisor\\
\today}\end{titlepage}
\restoregeometry
}
%title page end

% IMPRINT
\DeclareRobustCommand{\imprintpage}{
	\clearpage
	\thispagestyle{empty}
	

		~
	\vfill
	
	{\small
			\noindent \thectufituniversity \\
		\noindent \thectufitfaculty \\
	\noindent \textcopyright{} \thectufityear{} \thectufitauthorfull. \thectufitallrightsreservedlabel\\
		\noindent \textit{\thectufitcopyrighttext}
	
	\vspace{1em}
	
	\noindent \thectufitcitationlabel: \thectufitauthorsurnames{} \thectufitauthorgivennames. \textit{\thectufittitle}. \thectufitthesistype. \thectufituniversity, \thectufitfaculty, \thectufityear.
   }
}
% IMPRINT END

% captions settings
\DeclareCaptionLabelFormat{boxed}{%0.61,0.61,0.61
  \kern0.05em{\color{decoration}\rule{0.73em}{0.73em}}%
  \hspace*{0.67em}\bothIfFirst{#1}{~}#2}
\captionsetup{labelformat=boxed}
% captions settings end

% lists settings
\setlength\leftmargini  \parindent
\setlength\leftmarginii {1.2em}
\setlength\leftmarginiii{1.2em}
\setlength\leftmarginiv {1.2em}
\setlength\leftmarginv  {1.2em}
\setlength\leftmarginvi {1.2em}
\renewcommand\labelenumi{%
  \textcolor{enumgray}{\bfseries\upshape\mathversion{bold}\theenumi.}}
\renewcommand\labelenumii{%
  \textcolor{enumgray}{\bfseries\upshape\mathversion{bold}\theenumii.}}
\renewcommand\labelenumiii{%
  \textcolor{enumgray}{\bfseries\upshape\mathversion{bold}\theenumiii.}}
\renewcommand\labelenumiv{%
  \textcolor{enumgray}{\bfseries\upshape\mathversion{bold}\theenumiv.}}
% \makeatletter
\renewcommand\labelitemi{%
  \textcolor{enumgray}{\ifnum\@listdepth=\@ne
                                  \rule[0.3ex]{0.67em}{0.33em}%
                                \else
                                  \rule[0.4ex]{0.45em}{0.225em}%
                                \fi}}
% \makeatother
\renewcommand\labelitemii{%
  \textcolor{enumgray}{\rule[0.4ex]{0.45em}{0.225em}}}
\renewcommand\labelitemiii{%
  \textcolor{enumgray}{\bfseries\textasteriskcentered}}
\renewcommand\labelitemiv{%
  \textcolor{enumgray}{\bfseries\textperiodcentered}}
\renewcommand*\descriptionlabel[1]{%
  \hspace\labelsep\textcolor{enumgray}{\bfseries\mathversion{bold}#1}}
% lists settings end

%%%%%%%%%%%%%%
% FRONTMATTER SETTINGS
% no need to modify this part
%%%%%%%%%%%%%%
\DeclareRobustCommand{\frontmatterinit}{
\titleformat
{\chapter} % command
% [display] % shape
{} % format
{} % label
{} % sep
{\color{heading}\frontchapterfont \raggedleft} % before-code
[\vskip -2em] % after-code

\titleformat
{\section}
{\frontsectionfont\color{heading}}
{}
{}
{}

% \makeatletter
\@openrightfalse
% \makeatother
}
%%%%%%%%%%%%%%
% FRONTMATTER SETTINGS END
%%%%%%%%%%%%%%


% frontmatter headings
\def\frontchapterfont{\Large \bfseries}
\def\frontsectionfont{\large\bfseries}
\def\frontsubsectionfont{\large}
\def\frontsubsubsectionfont{\bfseries}

\setcounter{secnumdepth}{\@ctufitsecdepth} % numbering sections
\newcommand{\stopTOCentries}{
  \addtocontents{toc}{\protect\setcounter{tocdepth}{-1}}
}

\newcommand{\resumeTOCentries}{
  \addtocontents{toc}{\protect\setcounter{tocdepth}{\@ctufitsecdepth}} % table of content depth
}
% frontmatter headings end
% frontmatter pseudochapters: named part without printing actual chapter heading
% \makeatletter
\newcommand{\frontchapternotprinted}[1]{%
  \begingroup
  \let\@makechapterhead\@gobble % make \@makechapterhead do nothing
  \let\cleardoublepage\clearpage
  \chapter{#1}
  \endgroup
}
% \makeatother
% frontmatter pseudochapters end

% table of contents coloured chapters
% \makeatletter
\let\stdl@chapter\l@chapter
\renewcommand*{\l@chapter}[2]{%
  \stdl@chapter{\textcolor{heading}{#1}}{\textcolor{heading}{#2}}}
% \makeatother
% table of contents coloured chapters end

% headers and footers
% \makeatletter
\def\ps@plain{%chapter beginning
    \let\@evenhead\@empty%
    \let\@oddhead\@empty%
    \def\@evenfoot{\bfseries\color{headgray}\hfill\thepage\hfill}%
    \def\@oddfoot{\bfseries\color{headgray}\hfill\thepage\hfill}}
% \makeatother
\renewcommand{\chaptermark}[1]{\markboth{#1}{}}
\renewcommand{\sectionmark}[1]{\markright{#1}}
\pagestyle{fancy}
\fancyhf{}
\if@twoside
    \fancyhead[LE]{\leavevmode\smash{\llap{\color{headgray} \bfseries \thepage \hspace*{0em}}}}
    \fancyhead[RE]{\color{headgray}\bfseries\nouppercase{\leftmark}}
\else
    \fancyhead[L]{\leavevmode\smash{\llap{\color{headgray} \bfseries \thepage \hspace*{4em}}}}
    \fancyhead[R]{\color{headgray}\bfseries\nouppercase{\leftmark}}
\fi
\fancyhead[RO]{\leavevmode\smash{\rlap{\hspace*{0em}\color{headgray}\bfseries\thepage}}}
\fancyhead[LO]{\color{headgray}\bfseries\nouppercase{\rightmark}}
\setlength{\headheight}{14.05pt}
\addtolength{\topmargin}{-2.05pt}
\renewcommand{\headrulewidth}{0pt}
% headers and footers end


\newenvironment{abstrakt}{%
  \vspace*{18mm}
  \noindent
  {{\frontchapterfont\begin{flushleft}{\color{heading}Abstrakt}\end{flushleft}}}%
  \bigskip
  \noindent\ignorespaces}

\newenvironment{abstract}{%
  \vspace*{18mm}
  \noindent
  {{\frontchapterfont\begin{flushleft}{\color{heading}Abstract}\end{flushleft}}}%
  \bigskip
  \noindent\ignorespaces}
  
\newenvironment{declaration}{}

% acknowledgement page
\newenvironment{acknowledgmentpage}{\frontchapternotprinted{\if\@ctufitlang C{Poděkování}\else\if\@ctufitlang E{Acknowledgments}\else{Poďakovanie}\fi\fi}
~
\vfill
\hskip 0cm \begin{minipage}{0.7\textwidth}\itshape}{
\end{minipage}

\vfill

\vfill}
% acknowledgment page END

% declaration page
\newenvironment{declarationpage}{\frontchapternotprinted{\thectufitdeclarationlabel}
~
\vfill

  {{\frontchapterfont\begin{flushright}{\color{heading}\thectufitdeclarationlabel}\end{flushright}}}%
  \bigskip
  \noindent\ignorespaces
}{\vskip 1cm
\noindent
\if\@ctufitlang E{In}\else{V}\fi~\thectufitdeclarationplace{} \if\@ctufitlang C{dne}\else\if\@ctufitlang S{dňa}\else{on}\fi\fi~\thectufitdeclarationdate{}}
% declaration page END

% abstract page
\newenvironment{abstractpage}{\frontchapternotprinted{\if\@ctufitlang E{Abstract}\else{Abstrakt}\fi}
}{}
% abstract page END

\newenvironment{summarypage}{\chapter{\if\@ctufitlang C{Shrnutí}\else\if\@ctufitlang E{Summary}\else{Zhrnutie}\fi\fi}
\setlength{\columnsep}{1cm}
\begin{multicols}{2}\small
}{\end{multicols}}

%%%%%%%%%%%%%%%%%%%%
% MAINMATTER SETTINGS
% no need to modify this part
%%%%%%%%%%%%%%%%%%%%
\DeclareRobustCommand{\mainmatterinit}{
% \makeatletter
\@openrighttrue
% \makeatother

\titleformat
{\chapter} % command
[display] % shape
{ \LARGE \bfseries \raggedleft} % format
{ \textcolor{headbackgroundgray}{{\titlerule*[1pc]{\rule{0.25em}{0.25em}}}} \hspace{0.5ex} \color{black} \chaptername~\thechapter } % label
{-0.3cm} % sep
{\color{heading} \Huge \vskip 0.5cm} % before-code
[\vskip 1cm] % after-code

%vzhled nadpisů sekcí
\titleformat{\section}
  {\Large\bfseries\color{heading}}{\colorbox{headbackgroundgray}{{\color{black}\thesection}}}{1em}{}%[\vskip -1em]
  
\titleformat{\subsection}
  {\Large\bfseries\color{heading}}{{{\color{black}\thesubsection}}}{1em}{}%[\vskip -1em]
  
\titleformat{\subsubsection}
  {\large\bfseries\color{heading}}{{{\color{black}\thesubsubsection}}}{1em}{}%[\vskip -1em]

\ifnum\@ctufitsecdepth=4%if paragraph should be also styled
  \titleformat{\paragraph}
    {\bfseries\color{heading}}{{{\color{black}\theparagraph}}}{1em}{}%[\vskip -1em]
\fi
}
%%%%%%%%%%%%%%%%%%%%
% MAINMATTER SETTINGS END
%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%
% APPENDIX SETTINGS 
% no need to modify this part
%%%%%%%%%%%%%%%%%%%%
\DeclareRobustCommand{\appendixinit}{
\titleformat
{\chapter} % command
[display] % shape
{ \LARGE \bfseries \raggedleft} % format
{ \textcolor{headbackgroundgray}{{\titlerule*[1pc]{\rule{0.25em}{0.25em}}}} \hspace{0.5ex} \color{black} \appendixname~\thechapter } % label
{-0.3cm} % sep
{\color{heading} \Huge \vskip 0.5cm} % before-code
[\vskip 1cm] % after-code
}
%%%%%%%%%%%%%%%%%%%%
% APPENDIX SETTINGS END
%%%%%%%%%%%%%%%%%%%%

% theorems, proofs, definitions, etc.
\RequirePackage{amsthm}[2020/05/29]
\RequirePackage{mathtools}[2020/03/24]
\RequirePackage{amssymb}[2013/01/14]

\thm@headfont{%
  \textcolor{decoration}{$\blacktriangleright$}\nobreakspace\bfseries}
\def\th@remark{%
  \thm@headfont{%
    \textcolor{decoration}{$\blacktriangleright$}\nobreakspace}%
  \normalfont % body font
  \thm@preskip\topsep \divide\thm@preskip\tw@
  \thm@postskip\thm@preskip
}
\def\@endtheorem{\endtrivlist}%\@endpefalse
\renewenvironment{proof}[1][\proofname]{\par
  \pushQED{\qed}%
  \normalfont \topsep6\p@\@plus6\p@\relax
  \trivlist
  \item[\hskip\labelsep
        \color{black}\bfseries
    #1\@addpunct{.}]\ignorespaces
}{%
  \popQED\endtrivlist%\@endpefalse
}
\theoremstyle{plain}
\newtheorem{theorem}{\if\@ctufitlang C{Věta}\else\if\@ctufitlang E{Theorem}\else{Veta}\fi\fi}
\newtheorem{lemma}[theorem]{\if\@ctufitlang C{Tvrzení}\else\if\@ctufitlang E{Lemma}\else{Tvrdenie}\fi\fi}
\newtheorem{corollary}[theorem]{\if\@ctufitlang C{Důsledek}\else\if\@ctufitlang E{Corollary}\else{Dôsledok}\fi\fi}
\newtheorem{proposition}[theorem]{\if\@ctufitlang C{Návrh}\else\if\@ctufitlang E{Proposition}\else{Návrh}\fi\fi}
\newtheorem{definition}[theorem]{\if\@ctufitlang C{Definice}\else\if\@ctufitlang E{Definiton}\else{Definícia}\fi\fi}
\theoremstyle{definition}
\newtheorem{example}[theorem]{\if\@ctufitlang C{Příklad}\else\if\@ctufitlang E{Example}\else{Príklad}\fi\fi}
\theoremstyle{remark}
\newtheorem{note}[theorem]{\if\@ctufitlang C{Poznámka}\else\if\@ctufitlang E{Note}\else{Poznámka}\fi\fi}
\newtheorem*{note*}{\if\@ctufitlang C{Poznámka}\else\if\@ctufitlang E{Note}\else{Poznámka}\fi\fi}
\newtheorem{remark}[theorem]{\if\@ctufitlang C{Pozorování}\else\if\@ctufitlang E{Remark}\else{Pozorovanie}\fi\fi}
\newtheorem*{remark*}{\if\@ctufitlang C{Pozorování}\else\if\@ctufitlang E{Remark}\else{Pozorovanie}\fi\fi}
\numberwithin{theorem}{chapter}
% theorems, proofs, definitions, etc. end

\DeclareRobustCommand{\printabstractpage}{%
\begin{abstractpage}
\if\@ctufitlang E{%
\begin{abstract}%
\thectufitabstract
\end{abstract}

\vskip 0.5cm

{\noindent\color{heading}\bfseries Keywords\hspace{1em}}{\thectufitkeywords}}\else{%
\begin{abstrakt}%
\thectufitabstrakt
\end{abstrakt}

\vskip 0.5cm

{\noindent\color{heading}\bfseries Klíčová slova\hspace{1em}}{\thectufitklicovaslova}}\fi

\pagebreak 

\if\@ctufitlang E{%
\begin{abstrakt}%
\thectufitabstrakt
\end{abstrakt}

\vskip 0.5cm

{\noindent\color{heading}\bfseries Klíčová slova\hspace{1em}}{\thectufitklicovaslova}}\else{
\begin{abstract}%
\thectufitabstract
\end{abstract}

\vskip 0.5cm

{\noindent\color{heading}\bfseries Keywords\hspace{1em}}{\thectufitkeywords}}\fi
\end{abstractpage}
}

\newenvironment{chapterabstract}{\hfill\begin{minipage}{\dimexpr\textwidth-0.5cm}\itshape}{\end{minipage}\vskip 0.5cm\par\@afterindentfalse\@afterheading}

\AtBeginDocument{%
	\@ifpackageloaded{listings}{%
		\DeclareRobustCommand{\lstlistingname}{\thectufitlistinglabel}%
		\DeclareRobustCommand{\lstlistlistingname}{\thectufitlollabel}%
		\DeclareRobustCommand{\thectufitlistingscommand}{\lstlistoflistings}%
		\lstset{basicstyle=\small\ttfamily,keywordstyle=\bfseries,%
				backgroundcolor=\color{backgroundgray},%
				frame=single,framerule=0pt,xleftmargin=\fboxsep,xrightmargin=\fboxsep}%
	}{}%
	\@ifpackageloaded{minted}{%
		\DeclareRobustCommand{\listingscaption}{\thectufitlistinglabel}%
        		\SetupFloatingEnvironment{listing}{name=\listingscaption}
		\DeclareRobustCommand{\listoflistingscaption}{\thectufitlollabel}%
		\DeclareRobustCommand{\listlistingname}{\thectufitlollabel}%
		\DeclareRobustCommand{\thectufitlistingscommand}{\listoflistings}%
		\ifdefined\@ctufitthesisblackandwhite
 			\usemintedstyle{bw}%
			\setminted{bgcolor=backgroundgray}%
		\fi
		\setmintedinline{bgcolor={}}
	}{}%
}

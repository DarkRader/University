<h1>Semestral work - Database Systems</h1>

<section class="doc-section level-1"><h2 id="_title"><a class="anchor" href="#_title" aria-hidden="true"></a>Title</h2><p>List of legendary historical swords.</a></p>

<section class="doc-section level-1"><h2 id="_description"><a class="anchor" href="#_description" aria-hidden="true"></a>Description</h2><p>List of legendary historical Swords - is a company that is engaged in the collection of information about the well-known in the history of Swords. The firm structures all information about the characteristics of weapons, their owners, to whom they belong and the price they have. This is not all that this list contains, but it will be described in more detail below. The main reason why this list was made in order to facilitate the search of connoisseurs of Swords weapons that they want to buy or rent from the owners, and curious to follow the information about the swords that are of interest to them. And now we're going to describe exactly what this list looks like.

The `sword` has its own personal characteristics that distinguish it from others, but we can indeficate a particular sword by its unique id. In addition to the id, the weapon has additional characteristics, such as, insurance, type (claymore, bastard, katana, twine, yatagan, tulvar and so on), rank, condition (how well preserved), price, condition of lease and sale(we'll talk about lease and sale later) and other optional characteristics. Also, we should not forget, each sword has its own great `story` due to which we can get to know its history better.

The story can contain a lot of interesting information about the sword: when it was found, when it was made and by whom (if this information is known), who used it, what can be known to modern people, of course it can contain some description. Thus, we can say that everything related to the story will be contained here.

Each sword has its own `owner`, which can be an `person` or an `organization`, each of them can have its own characteristics, for example, the organization has the type to which it belongs, its unique regestation and name. A physical person has a name, a surname and a unique document number, but the number that identifies them has a separate section called `subject`.

Our company not only deals with the database, but also helps to buy and rent swords, edit databases (reduce the story of the sword), prepare contracts for `rent`, Sale and other things to trifles. For this activity we need `employees`(in our database they are assumed to be an individual) that will do it. He has in his characteristics the contract number, salary and schedule (it is not rumored and is usually characterized by what week and from how much to how many works, but since some have a free schedule, then they do not have a schedule, in the database it can be recorded in any style). In addition, we have clients (they can also be an individual or an organization) who through us can rent any sword from the owners, usually swords are rented for various exhibitions, thematic collections, museums and so on, in other cases it is not possible to rent a sword, but we have restrictions. Not every owner has plans to rent someone their gun. In that case, he can show it. We will find it in the owner section and it will be written there: `option_for_rent` and it has two variants (yes or no).

Id_number and contact details of owners, clients and employees are stored in one place in the subjetk section. In addition, each subjetk has an`address`. If someone wants to rent a sword, he can contact our employees and tell them about what action he wants to rent a sword, they will consult them and contact the owner directly. When we have the consent from the owner, we negotiate with the client about the dates and the price we have in relation to the market value of the sword, the number of days rented and transportation (if you have it).

Fortunately, we have cooperation with various international courier companies, and therefore we can advise you on the most suitable options from which you can choose, but this is definitely an optional opportunity. Then we sign the `contract`, in it we show the contract id, its status, the dates on which the sword will be rented and for what event, the name of the transport company, if you choose one . Moreover, almost everything will be the same if someone wants to buy a sword, but the contract will not contain the dates of the lease and for what event the lease will be. Then we can re-sign the contract. And one of our employees must deliver a new owner (if he was not before). 

However, this is how our company works, we hope it will be very useful for you.</a>.</p>

<section class="doc-section level-1"><h2 id="_conceptual_schema"><a class="anchor" href="_conceptual_schema" aria-hidden="true"></a>Conceptual scheme</h2></a>

![Conceptual scheme](https://user-images.githubusercontent.com/73800331/202199942-00d35b63-45d2-4e39-8695-e496f57c464b.png)

<section class="doc-section level-1"><h2 id="_loop"><a class="anchor" href="_loop" aria-hidden="true"></a>Loop discussion</h2><p>I'll try to explain why I got some loops:

Loop `contract - mec-owner-subjetk-person-employee-contract:` in my database in the contract can participate owner and employee. Both take the ID from the subject, as well as both can be person. In order to distinguish between them, we need the entities owner and employee. When a contract is concluded owner.id a employee.id they can not equal, and for this activity I need IO5 to avoid this opportunity.

Loop `contract-mec-owner-subjetk-contract:` in my database in the contract can participate client (binding subject - > contract) and owner. Both take the ID from the subject, as well as both can be person and organization. In order to distinguish between them, we need the client relationship (entity -> contract relationship) and the owner entity. When a contract is concluded subjekt.id a owner.id they can not equal, and for turo activity I need IO5 to avoid this opportunity.

Loop `contract-subject-person-contract:` in my database in the contract can participate client (binding subject - > contract) and employee. Both take the ID from the subject, as well as both can be person. In order to distinguish between them, we need the client link (subject Link -> contract) and the Employee entity. When a contract is concluded subjekt.id a employee.id they can not equal, and for this activity I need IO5 to avoid this opportunity.</a></p>

<section class="doc-section level-1"><h2 id="_relational_scheme"><a class="anchor" href="_relational_scheme" aria-hidden="true"></a>Relational scheme.</h2> <p>(here is an untranslated version from Czech, the name of the attribute entity in English can be viewed in the conceptual scheme).</a></p>

![Relational scheme](https://user-images.githubusercontent.com/73800331/202203202-4194cd57-8732-46e4-a57b-e3ad07d62a4b.jpeg)

<section class="doc-section level-1"><h2 id="_Queries"><a class="anchor" href="_Queries" aria-hidden="true"></a>Queries.</h2> <p>(only questions are translated here, attributes and entities are taken from the Czech version of the database).</a></p>

### Queries 1:

#### Natural:
Find the oldest sword found. List his id, status, and story(description, date_creation, country_creation, who_made, whos_use_it).

#### SQL:
select m.id_mec, m.stav, p.popis, p.datum_vytvareni, p.zeme_vytvareni, p.kym_byl_udelan, p.kdo_pouzival

from mec m join pribeh p on m.id_mec=p.id_mec

order by datum_vytvareni asc limit 1;

### Queries 2:

#### Natural:
Write all owners who have more than three swords. List the id and number of swords that the owners have and arrange the output in descending order.

#### SQL:
select ma.id_subjekt, count(m.id_mec) as pocet_meсu

from majitel ma join mec m using (id_subjekt)

group by ma.id_subjekt

having count(m.id_mec) >3

order by pocet_meсu desc

### Queries 3:

#### Natural:
How many swords are now in rent.

#### Relational algebra:
mec(status_pronajmu='v_pronajmu')

#### SQL:
SELECT DISTINCT *

FROM MEC

WHERE status_pronajmu = 'v_pronajmu';

### Queries 4:

#### Natural:
Id, names and surnames of employees who reduced each sword found in 'Japan'.

#### Relational algebra:
{{zamestanec_pribeh[id_subjekt, id_mec]
÷
{zamestanec_pribeh[zamestanec_pribeh.id_mec=pribeh.id_mec]pribeh(zeme_nalezu='Japan')}
[id_mec]}*fyzicka_osoba}[id_subjekt,jmeno,prijmeni]

### Queries 5:

#### Natural:
List the ID and address (id_subject, country, city, psc, street, number, room_number)of the owners who only have a claymor sword.

#### Relational algebra:
{{{{mec[mec.id_subjekt=majitel.id_subjekt] majitel}}[id_subjekt]
\
{mec(typ!='claymore')[mec.id_subjekt=majitel.id_subjekt] majitel}[id_subjekt]}*subjekt *adresa}
[id_subjekt, stat, mesto, psc, ulica, cislo, cislo_pokoje]

### Queries 6:

#### Natural:
Write all employees who are simultaneously owners, who have more than two swords and have a salary of more than $3000. Write their id, name, surname, number of documents, number of contracts, salary, telephone number and the number of swords they have and arrange the output in descending order.

#### SQL:
select m.id_subjekt,fz.jmeno, fz.prijmeni, fz.cislo_dokladu, z.cislo_smlouvy, z.plat,

s.telefonni_cislo, count(m.id_mec) as pocet_meсu

from zamestanec z join majitel ma using (id_subjekt) join fyzicka_osoba fz 

on ma.id_subjekt=fz.id_subjekt join subjekt s on fz.id_subjekt=s.id_subjekt

join mec m on ma.id_subjekt=m.id_subjekt

where plat>3000

group by fz.jmeno, fz.prijmeni, fz.cislo_dokladu, z.cislo_smlouvy, z.plat,

s.telefonni_cislo, m.id_subjekt

having count(m.id_mec) >2

order by pocet_meсu desc

### Queries 7:

#### Natural:
Find all owners who are organizations. Write their id, name, type_organization, registration and address (city, country and street)

#### Relational algebra:
{majitel*subjekt*organizace*adresa}[id_subjekt,nazev,typ_organizace,registrace,mesto,stat,ulica]

### Queries 8:

#### Natural:
Select employees named Cletus. Write name, salary, schedule and document number

#### Relational algebra:
{ zamestanec [zamestanec.id_subjekt=fyzicka_osoba.id_subjekt] fyzicka_osoba}(jmeno='Cletus')[jmeno,prijmeni,plat,grafik,cislo_dokladu]

### Queries 9:

#### Natural:
Employees who have never signed a contract. Write id, Name, Surname, salary and graphics.

#### Relational algebra:
{{zamestanec[id_subjekt]
\
{smlouva[smlouva.zamestanec_id_subjekt=zamestanec.id_subjekt > zamestanec}[id_subjekt]}
*zamestanec*fyzicka_osoba}[id_subjekt, jmeno,prijmeni,plat,grafik]

### Queries 10:

#### Natural:
Employees who reduced swords created in 'Japan' or 'Germany'. Write their id first and last name

#### Relational algebra:
{{{pribeh(zeme_vytvareni='Germany')[pribeh.id_mec=zamestanec_pribeh.id_mec]zamestanec_pribeh}
∪
{pribeh(zeme_vytvareni='Japan')[pribeh.id_mec=zamestanec_pribeh.id_mec]zamestanec_pribeh}}
*fyzicka_osoba}[id_subjekt,jmeno,prijmeni]

### Queries 11:

#### Natural:
Write information about the owner id, Document Number, name and surname, if it is a natural person, or id, registration, named and type of company, if it is an organization, if he owns a sword type tulvar in excellent condition, found in India '8.2.1874' year

#### Relational algebra:
{{mec(stav='excellent' ∧ typ='tulvar')*pribeh(datum_nalezu='8.2.1874' ∧ zeme_nalezu='India')}*majitel*subjekt}*>organizace

### Queries 12:

#### Natural:
Subjects that are not organizations

#### Relational algebra:
organizace!*>subjekt

### Queries 13:

#### Natural:
Employees who reduced swords created in 'Germany' and in 'Turkey'. Write their id, name and surname

#### Relational algebra:
{{{{{pribeh(zeme_nalezu='Germany')[pribeh.id_mec=zamestanec_pribeh.id_mec]zamestanec_pribeh}[id_subjekt]}
∩
{pribeh(zeme_nalezu='Turkey')[pribeh.id_mec=zamestanec_pribeh.id_mec]zamestanec_pribeh}[id_subjekt]}
*fyzicka_osoba}[id_subjekt,jmeno,prijmeni]}

### Queries 14:

#### Natural:
Checking a Category D1 query

#### Relational algebra:
zamestanec_pribeh[id_subjekt]
\
{{zamestanec_pribeh[id_subjekt, id_mec]
÷
{zamestanec_pribeh[zamestanec_pribeh.id_mec=pribeh.id_mec]pribeh(zeme_nalezu='Japan')}
[id_mec]*zamestanec*>pribeh*>zamestanec_pribeh}}[id_subjekt]

### Queries 15:

#### Natural:
Write all addresses from the database that are located in "Poland"(id_address, country, city), if the subject of the database is located at this address, write its id phone_number and e-mail

#### SQL:
select adresa.id_adresa, adresa.stat, adresa.mesto,

subjekt.id_subjekt, subjekt.telefonni_cislo,subjekt.email

from adresa left outer join subjekt

on adresa.id_adresa=subjekt.id_adresa

where adresa.stat='Poland'

### Queries 16:

#### Natural:
Write all employees whose salary is greater than 1000 and all owners who have status_lease 'no' combine these two lists into one to see who is both employee and owner

#### SQL:
select zamestanec.id_subjekt as zamestanec, zamestanec.plat,

majitel.id_subjekt as majitel, majitel.moznost_pronajmu

from majitel full outer join zamestanec

on majitel.id_subjekt=zamestanec.id_subjekt

where zamestanec.plat>1000 or majitel.moznost_pronajmu='Ne';

### Queries 17:

#### Natural:
Since people often borrow Swords of the katan type, they will increase salaries by 300 to all employees who were engaged in editing the story of such swords

#### SQL: 
begin;

select distinct fz.id_subjekt,fz.jmeno, fz.prijmeni, z.plat

from fyzicka_osoba fz join zamestanec z using(id_subjekt)

join zamestanec_pribeh zp on z.id_subjekt = zp.id_subjekt join pribeh p on zp.id_mec = p.id_mec

join mec m on p.id_mec = m.id_mec

where m.typ='katana';

update zamestanec

set plat=plat+300

where id_subjekt in(

    select z.id_subjekt
    
    from zamestanec z join zamestanec_pribeh zp on z.id_subjekt = zp.id_subjekt
    
    join pribeh p on zp.id_mec = p.id_mec join mec m on p.id_mec = m.id_mec
    
    where m.typ='katana'
    
    );
    
select distinct fz.id_subjekt,fz.jmeno, fz.prijmeni, z.plat

from fyzicka_osoba fz join zamestanec z using(id_subjekt)

join zamestanec_pribeh zp on z.id_subjekt = zp.id_subjekt join pribeh p on zp.id_mec = p.id_mec

join mec m on p.id_mec = m.id_mec

where m.typ='katana';

rollback;

### Queries 18:

#### Natural:
Create a view that only shows employees with a salary greater than 3,000. List their id, document_name, and name. Check the view with a question.

#### SQL:
create or replace view bohati as

select * from fyzicka_osoba

where exists (select 1 from zamestanec where

zamestanec.id_subjekt=fyzicka_osoba.id_subjekt and zamestanec.plat>3000 )

with check option;

select * from bohati;

### Queries 19:

#### Natural:
Remove all employees who are among the rich

#### SQL:
begin;

select count(id_subjekt) from bohati;

delete from zamestanec where id_subjekt in(select id_subjekt from bohati);

select count(id_subjekt) from bohati;

rollback;

### Queries 20:

#### Natural:
Write id, document_name, and names of all the rich employees who redacted swords.

#### SQL:
select * from fyzicka_osoba f where exists (select 1 from bohati b where b.id_subjekt=f.id_subjekt);

### Queries 21:

#### Natural:
List all entities that are organizations in our database. Sort the records by phone_number ascending and e-mail descending. We do not want to publish duplicate records.

#### SQL:
select distinct s.*

from subjekt s join organizace o on s.id_subjekt = o.id_subjekt

order by telefonni_cislo asc, email desc;

--nebo pomocí exists

select distinct *

from subjekt s where exists

(select * from organizace o where s.id_subjekt = o.id_subjekt)

order by telefonni_cislo asc, email desc;

--nebo pomocí in

select distinct * from subjekt s where s.id_subjekt in (select id_subjekt from organizace)

order by telefonni_cislo asc, email desc;

### Queries 22:

#### Natural:
How many swords did each employee modify. List its id, name, surname and number of modified swords.

#### SQL: 
select z.id_subjekt, fz.jmeno, fz.prijmeni, (select count(*)from zamestanec_pribeh zp

where zp.id_subjekt=z.id_subjekt) from zamestanec z

join fyzicka_osoba fz on z.id_subjekt=fz.id_subjekt

order by count desc;

### Queries 23:

#### Natural:
One of their current physical persons in the database decided to find a job with us. Make it to the table with the employee assign him contract_number and salary

#### SQL:
begin;

select * from zamestanec;

insert into zamestanec(id_subjekt, cislo_smlouvy, plat)

select id_subjekt, cislo_smlouvy, plat from(

select  round(60)+1 as id_subjekt, round(random()*5000)+1 as cislo_smlouvy, round(random()*5000)+1 as plat

from fyzicka_osoba 

) vstup order by random() limit 1;

select * from zamestanec;

rollback;

select * from zamestanec;

### Queries 24:

#### Natural:
How many swords that were leased(that is, have the status of closed) were transported by 'ship' for the action "study of the value of weapons". List id, type, id_contract, lease status_price, shipping, action, date_from and date_to)

#### SQL:
select m.id_mec, m.typ, s.id_smlouva, s.cena, 

s.stav_smlouvy, s.doprava, p.akce, p.obdobi_od, p.obdobi_do

from mec m join smlouva s on m.id_mec=s.id_mec join pronajem p

on s.id_smlouva=p.id_smlouva

where s.doprava='ship' and p.akce='study of the value of weapons'

and s.stav_smlouvy='uzavrena';

### Queries 25:

#### Natural:
Write the Ids of all participants in the contract, which has the status_contract 'preparation'.

#### SQL:
select sub.id_subjekt as klient, ma.id_subjekt as majitel, z.id_subjekt as zamestanec

from smlouva s join mec m on s.id_mec=m.id_mec

join zamestanec z on s.zamestanec_id_subjekt=z.id_subjekt

join subjekt sub on s.id_subjekt=sub.id_subjekt

join majitel ma on m.id_subjekt=ma.id_subjekt

where s.stav_smlouvy='priprava';

### Queries 26:

#### Natural:
The employee who wrote this query is in the Czech Republic and therefore write all owners who live in the Czech Republic, specifically their id owners and full address

#### SQL:
select ma.id_subjekt, a.id_adresa, a.stat, a.mesto, a.psc,

a.ulica, a.cislo, a.cislo_pokoje

from majitel ma join subjekt s on ma.id_subjekt=s.id_subjekt

join adresa a on s.id_adresa=a.id_adresa

where stat='Czech Republic';

<section class="doc-section level-1"><h2 id="_Conclusion"><a class="anchor" href="_Conclusion" aria-hidden="true"></a>Conclusion.</h2> <p>I encountered a number of problems while I was doing this semester's work and I think it turned out far from ideal, but nevertheless it provided me with a great opportunity to get acquainted with databases and learn how to simulate them, fill in, come up with queries in RA and SQL, which I find useful practice that will definitely help me in the future. The most difficult I managed: the first is the conceptual scheme. Although in the end it turned out to be quite simple, but it had to be reworked a little and understand very well how the links between the tables work. The second is the filling of tables. Although I used to use the table generator, but I then had to adjust a lot to consider various trifles between the tables, for example: it would be very strange if a katana-type sword was found somewhere in Germany and so on, although I think he could easily overlook a lot of things. Well, and the most demandingwere RA and SQL queries. In the beginning, everything seems very complicated(quite a lot of time passed after the test, so he had a lot to remember), but gradually I understood everything better and better and got a better idea of how it works. I was especially surprised by SQL, a little later, I understood how convenient and pleasant it is when you start to understand how it works and then neche returns to RA. But some questions became a real test and often it did not work to write what I originally wanted and had to redo something a lot of times, but overall it was an experience and it can be said that I have a pretty good feeling about this semester's work.</a></p>

<section class="doc-section level-1"><h2 id="_References"><a class="anchor" href="_References" aria-hidden="true"></a>References.</h2><p>
[1] Stránky předmětu DBS.BI-DBS FIT ČVUT Course Pages [online]. FIT ČVUT, 2022. Dostupné z: https://courses.fit.cvut.cz

[2] Vzorová semestrální práce [online]. FIT ČVUT, 2022. Dostupné z: https://users.fit.cvut.cz/~hunkajir/dbs2/main.xml

[3] Mockaroo Random Data Generator and API Mocking Tool. | JSON / CSV / SQL / Excel [online]. Mockaroo, 2022. Dostupné z: https://www.mockaroo.com/

[4] Stack Overflow - Where Developers Learn, Share, & Build Careers [online]. Stack Overflow, 2022. Dostupné z: https://stackoverflow.com/

[5] Wikipedia - internetové encyklopedii, kterou může upravovat každý [online]. Wikipedia, 2022. Dostupné z https://cs.wikipedia.org/wiki/Hlavn%C3%AD_strana</a></p>

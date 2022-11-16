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

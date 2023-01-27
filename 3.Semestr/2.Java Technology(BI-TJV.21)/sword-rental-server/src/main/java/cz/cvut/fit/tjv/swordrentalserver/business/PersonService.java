package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.PersonDto;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.SwordDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.ContractRepository;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.PersonRepository;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.SwordRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.server.ResponseStatusException;

import java.util.*;

@Service
//@Transactional(readOnly = true)
public class PersonService extends AbstractCrudService<Long, Person, PersonRepository> {

    private ContractRepository contractRepository;

    private SwordRepository swordRepository;

    private ContractService contractService;

    @Autowired
    public PersonService(PersonRepository personRepository, ContractRepository contractRepository, SwordRepository swordRepository, ContractService contractService) {
        super(personRepository);
        this.contractRepository = contractRepository;
        this.swordRepository = swordRepository;
        this.contractService = contractService;
    }

    public Person create(Person person)  {
        for (Sword sword: person.getWishList()) {
            swordRepository.findById(sword.getSwordId()).get().getPeopleWhoWishesForThisSword().add(person);
        }

        return repository.save(person);
    }

    @Transactional
    public ResponseEntity<Person> update(@RequestBody PersonDto personDto, @PathVariable Long id) {
        Optional<Person> person = super.readById(id);
        if(person.isEmpty()) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "NO SUCH PERSON");
        }
        person.get().setUsername(personDto.getUsername());
        person.get().setName(personDto.getName());
        person.get().setSurname(personDto.getSurname());
        person.get().setPhoneNumber(personDto.getPhoneNumber());
        person.get().setEmail(personDto.getEmail());
        Set<Sword> wishlist = new HashSet<>();
        for (Long sword: personDto.getWishList()) {
            wishlist.add(swordRepository.findById(sword).get());
            swordRepository.findById(sword).get().getPeopleWhoWishesForThisSword().add(person.get());
        }
        Set<Sword> alert = new HashSet<>();
        for(Long sword: personDto.getWantedSwordAlert()) {
            alert.add(swordRepository.findById(sword).get());
        }
        person.get().setWishList(wishlist);
        person.get().setWantedSwordAlert(alert);
        final Person finalUser = repository.save(person.get());
        return ResponseEntity.ok(finalUser);
    }

    public void deleteById(Long id) {
        Optional<Person> personOptional = readById(id);
        if(personOptional.isPresent()) {
            Person curPerson = personOptional.get();
            Collection<Contract> contractCollection = contractRepository.findAllByPerson(curPerson);

            for (Sword sword: curPerson.getWishList()) {
                swordRepository.findById(sword.getSwordId()).get().getPeopleWhoWishesForThisSword().remove(curPerson);
            }

            for(Contract contract: contractCollection) {
                contractService.deleteById(contract.getContractId());
            }

            repository.deleteById(id);
        } else {
            throw new NoSuchElementException("No such Person in database!");
        }
    }
}
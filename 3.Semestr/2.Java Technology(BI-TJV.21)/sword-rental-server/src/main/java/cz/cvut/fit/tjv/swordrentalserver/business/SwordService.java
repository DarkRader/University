package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.ContractDto;
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
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.server.ResponseStatusException;

import java.util.HashSet;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.Set;

@Service
//@Transactional(readOnly = true)
public class SwordService extends AbstractCrudService<Long, Sword, SwordRepository> {

    private ContractRepository contractRepository;

    private PersonRepository personRepository;

    @Autowired
    public SwordService(SwordRepository swordRepository, ContractRepository contractRepository, PersonRepository personRepository) {
        super(swordRepository);
        this.contractRepository = contractRepository;
        this.personRepository = personRepository;
    }

    @Transactional
    public ResponseEntity<Sword> update(@RequestBody SwordDto swordDto, @PathVariable Long id) {
        Optional<Sword> sword = super.readById(id);
        if(sword.isEmpty()) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "NO SUCH CONTRACT");
        }
        sword.get().setType(swordDto.getType());
        sword.get().setPrice(swordDto.getPrice());
        sword.get().setWeight(swordDto.getWeight());
        sword.get().setLength(swordDto.getLength());
        sword.get().setPeopleWhoWishesForThisSword(repository.findById(swordDto.getSwordId()).get().getPeopleWhoWishesForThisSword());
        Set<Person> newPeopleWhoWishesForThisSword = new HashSet<>();
        for (Long personId: swordDto.getPeopleWhoWishesForThisSword()) {
            newPeopleWhoWishesForThisSword.add(personRepository.findById(personId).get());
        }
        sword.get().setPeopleWhoWishesForThisSword(newPeopleWhoWishesForThisSword);
        final Sword finalSword = repository.save(sword.get());
        return ResponseEntity.ok(finalSword);
    }

    public void deleteById(Long id) {
        Optional<Sword> optionalSword = readById(id);
        if(optionalSword.isPresent()) {
            Sword curSword = optionalSword.get();
            for (Person person: curSword.getPeopleWhoWishesForThisSword()) {
                personRepository.findById(person.getPersonId()).get().getWantedSwordAlert().remove(curSword);
                personRepository.findById(person.getPersonId()).get().getWishList().remove(curSword);
            }
            repository.deleteById(id);
        } else {
            throw new NoSuchElementException("No such Sword in database!");
        }
    }
}
package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.ContractDto;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.PersonDto;
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

import java.time.LocalDateTime;
import java.util.*;

@Service
//@Transactional(readOnly = true)
public class ContractService extends AbstractCrudService<Long, Contract, ContractRepository> {

    private SwordRepository swordRepository;

    private PersonRepository personRepository;

    @Autowired
    public ContractService(ContractRepository contractRepository, SwordRepository swordRepository, PersonRepository personRepository) {
        super(contractRepository);
        this.swordRepository = swordRepository;
        this.personRepository = personRepository;
    }

    public Contract create(Contract contract)  {
        Sword curSword = swordRepository.findById(contract.getSword().getSwordId()).get();
        Collection<Sword> contractCollection = repository.findAllBySword(curSword);
        if(contractCollection.size() == 0) {

            Person curPerson = personRepository.findById(contract.getPerson().getPersonId()).get();

            curPerson.getWantedSwordAlert().remove(curSword);
            curPerson.getWishList().remove(curSword);
            curSword.getPeopleWhoWishesForThisSword().remove(curPerson);

            for (Person person: curSword.getPeopleWhoWishesForThisSword()) {
                personRepository.findById(person.getPersonId()).get().getWantedSwordAlert().remove(curSword);
            }

            return repository.save(contract);
        }
        return null;
    }

    @Transactional
    public ResponseEntity<Contract> update(@RequestBody ContractDto contractDto, @PathVariable Long id) {
        Optional<Contract> contract = super.readById(id);
        if(contract.isEmpty()) {
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, "NO SUCH CONTRACT");
        }
        contract.get().setEvent(contractDto.getEvent());
        contract.get().setPrice(contractDto.getPrice());
        contract.get().setDeliveryService(contractDto.getDeliveryService());
        contract.get().setPerson(personRepository.findById(contractDto.getPerson()).get());
        contract.get().setSword(swordRepository.findById(contractDto.getSword()).get());
        contract.get().setDate(contractDto.getDate());

        final Contract finalContract = repository.save(contract.get());
        return ResponseEntity.ok(finalContract);
    }

    public void deleteById(Long id) {
        Optional<Contract> contractOptional = readById(id);
        if(contractOptional.isPresent()) {
            Contract curContract = contractOptional.get();
            Sword curSword = swordRepository.findById(curContract.getSword().getSwordId()).get();

            for (Person wantThisSword : curSword.getPeopleWhoWishesForThisSword()) {
                Person curPerson = personRepository.findById(wantThisSword.getPersonId()).get();
                curPerson.getWantedSwordAlert().add(curSword);
            }

           repository.deleteById(id);
        } else {
            throw new NoSuchElementException("No such Contract in database!");
        }
    }

}

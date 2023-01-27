package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.entity.Contract;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.ContractRepository;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.PersonRepository;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.SwordRepository;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;

import java.util.HashSet;
import java.util.List;
import java.util.Optional;

@SpringBootTest
public class ContractServiceTest {
    @Autowired
    private ContractService contractService;

    @MockBean
    private ContractRepository contractRepository;

    @MockBean
    private PersonRepository personRepository;

    @MockBean
    private SwordRepository swordRepository;

    private Contract savedContract;
    private Contract updatedSavedContract;
    private Contract anotherSavedContract;
    private Contract unsavedContract;

    @BeforeEach
    public void setUp() {
        Person person1 = new Person(25, new HashSet<>(), "Lucky", "Grabi", "Nanor", 21512, "luckyf@mail.com", new HashSet<>());
        Person person2 = new Person(2, new HashSet<>(), "kuzn", "Antana", "Hlavitska", 215421422, "kfafw@mail.com", new HashSet<>());
        Sword sword1 = new Sword(32, "longsword", 2214142, 2, 22, new HashSet<>());
        Sword sword2 = new Sword(2, "tulvar", 521255, 34, 2414, new HashSet<>());
        Sword sword3 = new Sword(3, "yatagan", 525521, 3, 24, new HashSet<>());
        savedContract = new Contract(1L, "2023-1-12", 2124, "party", "ship", person1, sword1);
        updatedSavedContract = new Contract(1L, "2023-1-12", 2124, "birthday", "ship", person1, sword1);
        unsavedContract = new Contract(2L, "2022-12-20", 2141, "party", "ship", person1, sword2);
        anotherSavedContract = new Contract(3L, "2022-12-25", 4214, "museum", "flight", person2, sword3);

        Mockito.when(contractRepository.existsById(savedContract.getContractId())).thenReturn(true);
        Mockito.when(contractRepository.existsById(anotherSavedContract.getContractId())).thenReturn(true);
        Mockito.when(contractRepository.findById(savedContract.getContractId())).thenReturn(Optional.of(savedContract));
        Mockito.when(contractRepository.findById(unsavedContract.getContractId())).thenReturn(Optional.empty());
        Mockito.when(contractRepository.findAll()).thenReturn(List.of(savedContract, anotherSavedContract));
        Mockito.when(personRepository.findById(person1.getPersonId())).thenReturn(Optional.of(person1));
        Mockito.when(personRepository.findById(person2.getPersonId())).thenReturn(Optional.of(person2));
        Mockito.when(swordRepository.findById(sword1.getSwordId())).thenReturn(Optional.of(sword1));
        Mockito.when(swordRepository.findById(sword2.getSwordId())).thenReturn(Optional.of(sword2));
        Mockito.when(swordRepository.findById(sword3.getSwordId())).thenReturn(Optional.of(sword3));
    }

//    @Test
//    void create() {
//        contractService.create(unsavedContract);
//        Mockito.verify(contractRepository, Mockito.times(1)).save(unsavedContract);
//    }

    @Test
    void readById() {
        Assertions.assertEquals(Optional.of(savedContract), contractService.readById(savedContract.getContractId()));
        Assertions.assertEquals(Optional.empty(), contractService.readById(unsavedContract.getContractId()));
    }

    @Test
    void readAll() {
        Assertions.assertEquals(List.of(savedContract, anotherSavedContract), contractService.readAll());
    }
//
//    @Test
//    void update() {
//        Optional<Person> personOptional = personService.readById(updatedSavedPerson.getPersonId());
//        if(personOptional.isPresent()) {
//            PersonDto updatedSavedPersonDto = new PersonDto();
//            updatedSavedPersonDto.setPersonId(updatedSavedPerson.getPersonId());
//            updatedSavedPersonDto.setUsername(updatedSavedPerson.getUsername());
//            updatedSavedPersonDto.setName(updatedSavedPerson.getName());
//            updatedSavedPersonDto.setSurname(updatedSavedPerson.getSurname());
//            updatedSavedPersonDto.setPhoneNumber(updatedSavedPerson.getPhoneNumber());
//            updatedSavedPersonDto.setEmail(updatedSavedPerson.getEmail());
//            updatedSavedPersonDto.setWantedSwordAlert(new HashSet<>());
//            updatedSavedPersonDto.setWishList(new HashSet<>());
//
//            PersonDto unsavedPersonDto = new PersonDto();
//            unsavedPersonDto.setPersonId(unsavedPersonDto.getPersonId());
//            unsavedPersonDto.setUsername(unsavedPersonDto.getUsername());
//            unsavedPersonDto.setName(unsavedPersonDto.getName());
//            unsavedPersonDto.setSurname(unsavedPersonDto.getSurname());
//            unsavedPersonDto.setPhoneNumber(unsavedPersonDto.getPhoneNumber());
//            unsavedPersonDto.setEmail(unsavedPersonDto.getEmail());
//            unsavedPersonDto.setWantedSwordAlert(new HashSet<>());
//            unsavedPersonDto.setWishList(new HashSet<>());
//            personService.update(updatedSavedPersonDto, updatedSavedPerson.getPersonId());
//            Mockito.verify(personRepository, Mockito.times(1)).save(updatedSavedPerson);
//
////            Assertions.assertThrows(NoSuchElementException.class, () -> personService.update(unsavedPersonDto, unsavedPerson.getPersonId()));
//        }
//    }

//    @Test
//    void deleteById() {
//        contractService.deleteById(savedContract.getContractId());
////        Mockito.verify(contractRepository, Mockito.times(1)).deleteById(savedContract.getContractId());
//
//         Assertions.assertThrows(NoSuchElementException.class, () -> contractService.deleteById(unsavedContract.getContractId()));
//    }
}

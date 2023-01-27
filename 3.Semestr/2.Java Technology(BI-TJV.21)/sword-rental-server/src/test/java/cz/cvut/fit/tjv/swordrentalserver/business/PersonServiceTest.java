package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.PersonDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.PersonRepository;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.web.server.ResponseStatusException;

import java.util.HashSet;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

@SpringBootTest
public class PersonServiceTest {
    @Autowired
    private PersonService personService;

    @MockBean
    private PersonRepository personRepository;

    private Person savedPerson;
    private Person updatedSavedPerson;
    private Person anotherSavedPerson;
    private Person unsavedPerson;

    @BeforeEach
    public void setUp() {
        savedPerson = new Person(1L, new HashSet<>(), "kuznear1", "Anton", "Black", 21515212, "karbackOf@mail.com", new HashSet<>());
        updatedSavedPerson = new Person(1L, new HashSet<>(), "DarkRader", "Anton", "Black", 21515212, "karbackOf@mail.com", new HashSet<>());
        unsavedPerson = new Person(2L, new HashSet<>(), "kuzn", "Antana", "Hlavitska", 215421422, "kfafw@mail.com", new HashSet<>());
        anotherSavedPerson = new Person(3L, new HashSet<>(), "HopeRader", "Ales", "Radny", 215212, "karkOf@mail.com", new HashSet<>());

        Mockito.when(personRepository.existsById(savedPerson.getPersonId())).thenReturn(true);
        Mockito.when(personRepository.existsById(anotherSavedPerson.getPersonId())).thenReturn(true);
        Mockito.when(personRepository.findById(savedPerson.getPersonId())).thenReturn(Optional.of(savedPerson));
        Mockito.when(personRepository.findById(unsavedPerson.getPersonId())).thenReturn(Optional.empty());
        Mockito.when(personRepository.findAll()).thenReturn(List.of(savedPerson, anotherSavedPerson));

    }

    @Test
    void create() {
        personService.create(unsavedPerson);
        Mockito.verify(personRepository, Mockito.times(1)).save(unsavedPerson);
    }

    @Test
    void readById() {
        Assertions.assertEquals(Optional.of(savedPerson), personService.readById(savedPerson.getPersonId()));
        Assertions.assertEquals(Optional.empty(), personService.readById(unsavedPerson.getPersonId()));
    }

    @Test
    void readAll() {
        Assertions.assertEquals(List.of(savedPerson, anotherSavedPerson), personService.readAll());
    }

    @Test
    void update() {
        Optional<Person> personOptional = personService.readById(updatedSavedPerson.getPersonId());
        if(personOptional.isPresent()) {
            PersonDto updatedSavedPersonDto = new PersonDto();
            updatedSavedPersonDto.setPersonId(updatedSavedPerson.getPersonId());
            updatedSavedPersonDto.setUsername(updatedSavedPerson.getUsername());
            updatedSavedPersonDto.setName(updatedSavedPerson.getName());
            updatedSavedPersonDto.setSurname(updatedSavedPerson.getSurname());
            updatedSavedPersonDto.setPhoneNumber(updatedSavedPerson.getPhoneNumber());
            updatedSavedPersonDto.setEmail(updatedSavedPerson.getEmail());
            updatedSavedPersonDto.setWantedSwordAlert(new HashSet<>());
            updatedSavedPersonDto.setWishList(new HashSet<>());

            PersonDto unsavedPersonDto = new PersonDto();
            unsavedPersonDto.setPersonId(unsavedPersonDto.getPersonId());
            unsavedPersonDto.setUsername(unsavedPersonDto.getUsername());
            unsavedPersonDto.setName(unsavedPersonDto.getName());
            unsavedPersonDto.setSurname(unsavedPersonDto.getSurname());
            unsavedPersonDto.setPhoneNumber(unsavedPersonDto.getPhoneNumber());
            unsavedPersonDto.setEmail(unsavedPersonDto.getEmail());
            unsavedPersonDto.setWantedSwordAlert(new HashSet<>());
            unsavedPersonDto.setWishList(new HashSet<>());
            personService.update(updatedSavedPersonDto, updatedSavedPerson.getPersonId());
            Mockito.verify(personRepository, Mockito.times(1)).save(updatedSavedPerson);

            Assertions.assertThrows(ResponseStatusException.class, () -> personService.update(unsavedPersonDto, unsavedPerson.getPersonId()));
        }
    }

    @Test
    void deleteById() {
        personService.deleteById(savedPerson.getPersonId());
        Mockito.verify(personRepository, Mockito.times(1)).deleteById(savedPerson.getPersonId());

        Assertions.assertThrows(NoSuchElementException.class, () -> personService.deleteById(unsavedPerson.getPersonId()));
    }
}

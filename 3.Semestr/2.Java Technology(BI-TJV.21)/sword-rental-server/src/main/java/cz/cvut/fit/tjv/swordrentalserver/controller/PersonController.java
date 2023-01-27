package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.AbstractCrudService;
import cz.cvut.fit.tjv.swordrentalserver.business.PersonService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.PersonDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.PersonRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.function.Function;

@RestController
@RequestMapping("/persons")
public class PersonController extends AbstractCrudController<Person, PersonDto, PersonRepository> {

    private final PersonService personService;
    public PersonController(AbstractCrudService<Long, Person, PersonRepository> service, Function<Person, PersonDto> toDtoConverter, Function<PersonDto, Person> toEntityConverter, PersonService personService) {
        super(service, toDtoConverter, toEntityConverter);
        this.personService = personService;
    }

    @PutMapping("/{id}")
    public ResponseEntity<Person> update(@RequestBody PersonDto personDto, @PathVariable Long id) {
        return personService.update(personDto, id);
    }

}

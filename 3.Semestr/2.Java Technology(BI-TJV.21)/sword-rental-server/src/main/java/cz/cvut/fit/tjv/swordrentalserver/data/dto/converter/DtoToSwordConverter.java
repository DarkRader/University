package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

import cz.cvut.fit.tjv.swordrentalserver.business.PersonService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.SwordDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.HashSet;
import java.util.Set;
import java.util.function.Function;

@Component
public class DtoToSwordConverter implements Function<SwordDto, Sword>  {
    @Autowired
    private ModelMapper modelMapper;

    private final PersonService personService;

    public DtoToSwordConverter(PersonService personService) {
        this.personService = personService;
    }

    @Override
    public Sword apply(SwordDto swordDto) {
        Sword newSword = modelMapper.map(swordDto, Sword.class);
        Set<Person> newPeopleWhoWishesForThisSword = new HashSet<>();
        for (Long personId: swordDto.getPeopleWhoWishesForThisSword()) {
            newPeopleWhoWishesForThisSword.add(personService.readById(personId).get());
        }
        newSword.setPeopleWhoWishesForThisSword(newPeopleWhoWishesForThisSword);
        return newSword;
    }
}
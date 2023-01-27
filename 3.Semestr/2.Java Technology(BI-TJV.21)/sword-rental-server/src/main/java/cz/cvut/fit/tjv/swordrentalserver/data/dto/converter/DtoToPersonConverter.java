package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

import cz.cvut.fit.tjv.swordrentalserver.business.SwordService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.PersonDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Person;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import org.modelmapper.ModelMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.HashSet;
import java.util.Set;
import java.util.function.Function;

@Component
public class DtoToPersonConverter implements Function<PersonDto, Person> {
    @Autowired
    private ModelMapper modelMapper;

    private final SwordService swordService;

    public DtoToPersonConverter(SwordService swordService) {
        this.swordService = swordService;
    }

    @Override
    public Person apply(PersonDto personDto) {
        Person newPerson = modelMapper.map(personDto, Person.class);
        Set<Sword> alertSwordList = new HashSet<>();
        Set<Sword> newWishList = new HashSet<>();
        for (Long alertId : personDto.getWantedSwordAlert()) {
            alertSwordList.add(swordService.readById(alertId).get());
        }
        newPerson.setWantedSwordAlert(alertSwordList);

        for (Long wishListId: personDto.getWishList()) {
            newWishList.add(swordService.readById(wishListId).get());
        }
        newPerson.setWantedSwordAlert(alertSwordList);
        newPerson.setWishList(newWishList);
        return newPerson;
    }
}

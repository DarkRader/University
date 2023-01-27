package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

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
public class PersonToDtoConverter implements Function<Person, PersonDto> {
    @Autowired
    private ModelMapper modelMapper;

    @Override
    public PersonDto apply(Person person) {
        PersonDto newPersonDto = new PersonDto();
        newPersonDto.setPersonId(person.getPersonId());
        newPersonDto.setName(person.getName());
        newPersonDto.setSurname(person.getSurname());
        newPersonDto.setEmail(person.getEmail());
        newPersonDto.setPhoneNumber(person.getPhoneNumber());
        newPersonDto.setUsername(person.getUsername());
        Set<Long> alertSwordListDto = new HashSet<>();
        Set<Long> newWishListDto = new HashSet<>();
        for (Sword alertSwordId: person.getWantedSwordAlert()) {
            alertSwordListDto.add(alertSwordId.getSwordId());
        }
        for (Sword wishListId: person.getWishList()) {
            newWishListDto.add(wishListId.getSwordId());
        }
        newPersonDto.setWantedSwordAlert(alertSwordListDto);
        newPersonDto.setWishList(newWishListDto);
        return newPersonDto;
    }
}

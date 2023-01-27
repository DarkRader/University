package cz.cvut.fit.tjv.swordrentalserver.data.dto.converter;

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
public class SwordToDtoConverter implements Function<Sword, SwordDto> {
    @Autowired
    private ModelMapper modelMapper;

    @Override
    public SwordDto apply(Sword sword) {
        SwordDto newSwordDto = new SwordDto();
        newSwordDto.setSwordId(sword.getSwordId());
        newSwordDto.setType(sword.getType());
        newSwordDto.setPrice(sword.getPrice());
        newSwordDto.setLength(sword.getLength());
        newSwordDto.setWeight(sword.getWeight());
        Set<Long> newPeopleWhoWishesForThisSwordDto = new HashSet<>();
        for (Person personId: sword.getPeopleWhoWishesForThisSword()) {
            newPeopleWhoWishesForThisSwordDto.add(personId.getPersonId());
        }
        newSwordDto.setPeopleWhoWishesForThisSword(newPeopleWhoWishesForThisSwordDto);
        return newSwordDto;
    }
}

package cz.cvut.fit.tjv.swordrentalserver.business;

import cz.cvut.fit.tjv.swordrentalserver.data.dto.SwordDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.SwordRepository;
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
public class SwordServiceTest {
    @Autowired
    private SwordService swordService;

    @MockBean
    private SwordRepository swordRepository;

    private Sword savedSword;
    private Sword updatedSavedSword;
    private Sword anotherSavedSword;
    private Sword unsavedSword;

    @BeforeEach
    public void setUp() {
        savedSword = new Sword(1L, "katana", 214542, 21, 222, new HashSet<>());
        updatedSavedSword = new Sword(1L, "yatagan", 214542, 21, 222, new HashSet<>());
        unsavedSword = new Sword(2L, "tulvar", 521255, 34, 2414, new HashSet<>());
        anotherSavedSword = new Sword(3L, "yatagan", 525521, 3, 24, new HashSet<>());

        Mockito.when(swordRepository.existsById(savedSword.getSwordId())).thenReturn(true);
        Mockito.when(swordRepository.existsById(anotherSavedSword.getSwordId())).thenReturn(true);
        Mockito.when(swordRepository.findById(savedSword.getSwordId())).thenReturn(Optional.of(savedSword));
        Mockito.when(swordRepository.findById(unsavedSword.getSwordId())).thenReturn(Optional.empty());
        Mockito.when(swordRepository.findAll()).thenReturn(List.of(savedSword, anotherSavedSword));

    }

    @Test
    void create() {
        swordService.create(unsavedSword);
        Mockito.verify(swordRepository, Mockito.times(1)).save(unsavedSword);
    }

    @Test
    void readById() {
        Assertions.assertEquals(Optional.of(savedSword), swordService.readById(savedSword.getSwordId()));
        Assertions.assertEquals(Optional.empty(), swordService.readById(unsavedSword.getSwordId()));
    }

    @Test
    void readAll() {
        Assertions.assertEquals(List.of(savedSword, anotherSavedSword), swordService.readAll());
    }

    @Test
    void update() {
        Optional<Sword> swordOptional = swordService.readById(updatedSavedSword.getSwordId());
        if(swordOptional.isPresent()) {
            SwordDto updatedSavedSwordDto = new SwordDto();
            updatedSavedSwordDto.setSwordId(updatedSavedSword.getSwordId());
            updatedSavedSwordDto.setType(updatedSavedSword.getType());
            updatedSavedSwordDto.setPrice(updatedSavedSword.getPrice());
            updatedSavedSwordDto.setLength(updatedSavedSword.getLength());
            updatedSavedSwordDto.setWeight(updatedSavedSword.getWeight());
            updatedSavedSwordDto.setPeopleWhoWishesForThisSword(new HashSet<>());

            SwordDto unsavedSwordDto = new SwordDto();
            unsavedSwordDto.setSwordId(unsavedSword.getSwordId());
            unsavedSwordDto.setType(unsavedSword.getType());
            unsavedSwordDto.setPrice(unsavedSword.getPrice());
            unsavedSwordDto.setLength(unsavedSword.getLength());
            unsavedSwordDto.setWeight(unsavedSword.getWeight());
            unsavedSwordDto.setPeopleWhoWishesForThisSword(new HashSet<>());
            swordService.update(updatedSavedSwordDto, updatedSavedSword.getSwordId());
            Mockito.verify(swordRepository, Mockito.times(1)).save(updatedSavedSword);

            Assertions.assertThrows(ResponseStatusException.class, () -> swordService.update(unsavedSwordDto, unsavedSword.getSwordId()));
        }
    }

    @Test
    void deleteById() {
        swordService.deleteById(savedSword.getSwordId());
        Mockito.verify(swordRepository, Mockito.times(1)).deleteById(savedSword.getSwordId());

         Assertions.assertThrows(NoSuchElementException.class, () -> swordService.deleteById(unsavedSword.getSwordId()));
    }
}

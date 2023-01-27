package cz.cvut.fit.tjv.swordrentalserver.controller;

import cz.cvut.fit.tjv.swordrentalserver.business.AbstractCrudService;
import cz.cvut.fit.tjv.swordrentalserver.business.SwordService;
import cz.cvut.fit.tjv.swordrentalserver.data.dto.SwordDto;
import cz.cvut.fit.tjv.swordrentalserver.data.entity.Sword;
import cz.cvut.fit.tjv.swordrentalserver.data.repository.SwordRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.function.Function;

@RestController
@RequestMapping("/swords")
public class SwordController extends AbstractCrudController<Sword, SwordDto, SwordRepository> {

    private final SwordService swordService;

    public SwordController(AbstractCrudService<Long, Sword, SwordRepository> service, Function<Sword, SwordDto> toDtoConverter, Function<SwordDto, Sword> toEntityConverter, SwordService swordService) {
        super(service, toDtoConverter, toEntityConverter);
        this.swordService = swordService;
    }

    @PutMapping("/{id}")
    public ResponseEntity<Sword> update(@RequestBody SwordDto swordDto, @PathVariable Long id) {
        return swordService.update(swordDto, id);
    }
}

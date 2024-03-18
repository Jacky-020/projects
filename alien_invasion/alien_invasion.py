import pygame
from pygame.sprite import Sprite


import sys
import copy
# Settings hold all foundamental values that are to be adjusted by programmer / players
# Game control the main loop of events during the game, check the input and check the collision 
# Alien control the behavior of individual alien
# Scoreboard prepares surfaces for the display of score in Game
# Button prepare the Surface for the Start button


class Settings:
    
    def __init__(self):
        pygame.init()
        self.screen_height = 600
        self.screen_width = 1200
        self.bg_color = (135, 206, 235)

        self.ship_image = './rocket.jpg'
        self.ship_speed = 0.1
        
        self.bullet_speed = 3.0
        self.bullet_width, self.bullet_height = 15, 3
        self.bullet_color = (255, 0, 0)
        self.bullet_limit = 3

        self.alien_image = './alien.png'
        self.alien_speed = 0.1
        self.alien_separation_muliplier = 1.5

        self.button_color = (0, 255, 0)
        self.button_width, self.button_height = 100, 60
        self.button_text_color = (255, 255, 255)
        self.button_fontsize = 24
        self.button_text = "Start"

        self.scoreboard_text_color = (30, 30, 30)
class Game:

    def __init__(self):
        self.settings = Settings()
        self.screen = pygame.display.set_mode((self.settings.screen_width, self.settings.screen_height))
        self.screen_rect = self.screen.get_rect()

        self.key_pressed = {
            pygame.K_UP: False,
            pygame.K_DOWN: False,
            pygame.K_LALT : False
        }
        self.status = Status(self)
        self.ship = Ship(self)
        self.aliens = pygame.sprite.Group()
        self.bullets = pygame.sprite.Group()
        self.button = Button(self)
        self.scoreboard = Scoreboard(self)

    def run(self):
        while True:
            if self.status.game_on:
                self._update_alien()
                self.ship.update()
                self._update_bullets()
                self._check_collision()
            self._check_events()
            self._update_screen()

    def _check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self._quit()
            if event.type ==  pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    self._quit()
                if event.key == pygame.K_SPACE:
                    self._fire()
                    continue
                self.key_pressed[event.key] = True
            if event.type == pygame.KEYUP:
                self.key_pressed[event.key] = False
            if event.type == pygame.MOUSEBUTTONDOWN:
                self._check_button()

    def _check_button(self):
        if self.button.rect.collidepoint(pygame.mouse.get_pos()):
            self.status.game_on = True
        
    def _quit(self):
        sys.exit()

    def _check_collision(self):
        self.check_alien_ship_collision()
        self.check_bullet_alien_collision()

    def _update_alien(self):
        for alien in self.aliens:
            alien.update()
            if alien.out_of_screen():
                self.aliens.empty() 
        if len(self.aliens) == 0:
            self._setting_aliens()
        

    def _setting_aliens(self):
        alien = Alien(self)
        ship_height = self.ship.rect.height
        alien_height = alien.rect.height
        available_space = self.screen_rect.height - 0.5 * ship_height
        multiply_alien = available_space // alien_height
        num_row = int(multiply_alien / self.settings.alien_separation_muliplier) 
        #(available_space - alien.rect.height) // (2 * alien.rect.height) + 1
        # print(num_row)
        offset = (self.settings.screen_height - 
                  ((self.settings.alien_separation_muliplier * num_row - 1) * alien_height)) / 2
        for row_num in range(num_row):
            self._setting_alien(offset)
            offset += self.settings.alien_separation_muliplier * alien.rect.height

    def _setting_alien(self, offset):
        alien = Alien(self)
        alien.rect.y = offset
        self.aliens.add(alien)

    def _update_bullets(self):
        for bullet in self.bullets.copy():
            if bullet.out_of_screen():
                self.bullets.remove(bullet)
        # for bullet in self.bullets:
            bullet.update()

    def _fire(self):
        if len(self.bullets) >= self.settings.bullet_limit:
            return 
        self.bullets.add(Bullet(self))

    def check_bullet_alien_collision(self):
        for alien in self.aliens:
            bullets = pygame.sprite.spritecollideany(alien, self.bullets)
            if bullets:
                self.status.score += 1
                self.scoreboard.prep_score()
                self.aliens.remove(alien)
                self.bullets.remove(bullets)

    def check_alien_ship_collision(self):
        aliens = pygame.sprite.spritecollide(self.ship, self.aliens, False)
        if not aliens:
            return
        for alien in aliens: ## why no need .copy()
            self.status.life -= 1
            self.scoreboard.prep_score()
            if self.status.life <= 0:
                self._reset()
            self.aliens.remove(alien)

    def _reset(self):
        self.aliens.empty()
        self.bullets.empty()
        self.ship.reset()
        self.status.dynamic_setting()
        self.scoreboard.prep_score()

    def _update_screen(self):
        self.screen.fill(self.settings.bg_color)
        if self.status.game_on:
            self.aliens.draw(self.screen)
            for bullet in self.bullets:
                bullet.blitme()
            self.ship.blitme()
            self.scoreboard.show_score()
        else:
            self.button.blitme()
        pygame.display.flip()

class Ship(Sprite):

    def __init__(self, game) -> None:
        super().__init__()

        self.settings = game.settings
        self.screen = game.screen
        self.screen_rect = game.screen_rect
        self.key_pressed =  game.key_pressed

        self.image = pygame.image.load(self.settings.ship_image)
        self.image = pygame.transform.scale_by(self.image, 0.4)
        set_image(self.image)

        self.rect = self.image.get_rect()
        self.reset()

    def reset(self):
        self.rect.midright = self.screen_rect.midright
        self.y = self.rect.y

    def update(self):
        if self.key_pressed[pygame.K_LALT]:
            speed = self.settings.ship_speed * 3
        else:
            speed = self.settings.ship_speed
        if self.key_pressed[pygame.K_UP] and self.rect.top >= self.screen_rect.top:
            self.y -= speed
            self.rect.y = self.y
        if self.key_pressed[pygame.K_DOWN] and self.rect.bottom <= self.screen_rect.bottom:
            self.y += speed
            self.rect.y = self.y

    def blitme(self):
        self.screen.blit(self.image, self.rect)

class Alien(Sprite):

    def __init__(self, game) -> None:
        super().__init__()
        self.settings = game.settings
        self.screen = game.screen
        self.screen_rect = game.screen_rect

        self.image = pygame.image.load(self.settings.alien_image)
        self.image = pygame.transform.scale_by(self.image, 0.05)
        set_image(self.image)
        self.rect = self.image.get_rect()
        self.rect.left = self.screen_rect.left
        self.x = self.rect.x

    def update(self):
        self.x += self.settings.alien_speed
        self.rect.x = self.x   

    def out_of_screen(self):
        return self.rect.left > self.screen_rect.right
        
class Bullet(Sprite):

    def __init__(self, game) -> None:
        super().__init__()
        self.settings = game.settings
        self.screen = game.screen
        self.screen_rect = game.screen_rect

        self.rect = pygame.Rect(0, 0, self.settings.bullet_width, self.settings.bullet_height)
        self.rect.midleft = game.ship.rect.midleft

        self.x = self.rect.x
        pass

    def update(self):
        self.x -= self.settings.bullet_speed
        self.rect.x = self.x

    def out_of_screen(self):
        return self.rect.right < self.screen_rect.left
    
    def blitme(self):
        pygame.draw.rect(self.screen, self.settings.bullet_color, self.rect)
    
class Button(Sprite):

    def __init__(self, game): 
        self.settings = game.settings
        self.screen = game.screen
        self.screen_rect = game.screen_rect

        self.rect = pygame.rect.Rect(0, 0, self.settings.button_width, self.settings.button_height)
        self.rect.center = self.screen_rect.center
        self.font = pygame.font.SysFont(None, self.settings.button_fontsize)
        self._prep_msg()

    def _prep_msg(self):
        self.msg_image = self.font.render(self.settings.button_text, True, 
                                          self.settings.button_text_color, self.settings.button_color)
        self.msg_rect = self.msg_image.get_rect()
        self.msg_rect.center = self.rect.center

    def blitme(self):
        self.screen.fill(self.settings.button_color, self.rect)
        self.screen.blit(self.msg_image, self.msg_rect)

class Status:
    def __init__(self, game) -> None:
        self.dynamic_setting()
        pass

    def dynamic_setting(self):
        self.game_on = False
        self.life = 3
        self.score = 0

class Scoreboard(Sprite):
    
    def __init__(self, game):

        self.screen = game.screen
        self.screen_rect = game.screen_rect
        self.settings = game.settings 
        self.status = game.status

        self.font = pygame.font.SysFont(None, 48)
        self.prep_score()

    def prep_score(self):
        score_text = "score : " + str(self.status.score) + " lives : " +  str(self.status.life) 
        self.score_image = self.font.render(score_text, True, 
                                            self.settings.scoreboard_text_color, self.settings.bg_color)
        self.score_rect = self.score_image.get_rect()
        self.score_rect.right = self.screen_rect.right -20
        self.score_rect.top = 20

    def show_score(self):
        self.screen.blit(self.score_image, self.score_rect)

def set_image(image):
    image_bg_color = image.get_at((0,0))
    image.set_colorkey(image_bg_color)
    image = image.convert_alpha(image)


Game().run()
#ifndef UTILS_H
#define UTILS_H

#define SET(REG, BIT) (REG |= (1 << BIT))
#define UNSET(REG, BIT) (REG &= ~(1 << BIT))

#endif
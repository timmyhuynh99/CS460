/*******************************************************
*                      t.c file                        *
*Edited by Michael Berger                              *
*******************************************************/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;
GD    *gp;
INODE *ip;
DIR   *dp;

char buf1[BLK], buf2[BLK];
int color = 0x0A;
u8 ino;

main()
{ 
  u16    i, iblk, check;
  char   c, *temp;

  prints("read block# 2 (GD)\n\r");
  getblk((u16)2, buf1);
  gp = (GD *)buf1;
  iblk = (u16)gp->bg_inode_table;  
  
// 1. WRITE YOUR CODE to get iblk = bg_inode_table block number
  prints("inode_block=");
  putc(iblk+'0');
  prints("\n\r");
  getc();
  
// 2. WRITE YOUR CODE to get root inode
  prints("read inodes begin block to get root inode\n\r");
  getblk(iblk, buf1);  // read the inode block into buf1
  ip = (INODE *)buf1 + 1;  // point ip to the root Inode, which is the second Inode

// 3. WRITE YOUR CODE to step through the data block of root inode

   
// 4. print file names in the root directory /
  prints("read data block of root DIR\n\r");

  for (i = 0; i < 12; i++)
    {
      if ((u16)ip->i_block[i] == 0)
      {
        prints("\n\rNo more directorys!\n\r");
        break;
      }
      else
      {
        getblk((u16)ip->i_block[i], buf2);
        gp = (GD *)buf2;
        
        dp = (DIR *)buf2;
        check = 0;
        while (check == 0)
        {
            strncpy(temp, dp->name, dp->name_len);
            temp[dp->name_len] = 0;
            if (temp || strlen(temp + '\0') == 0)
              check = 1;
            else
            {
              prints(temp); putc(' ');              
              dp = (DIR *)((char *)dp + dp->rec_len);
            }
        }

          /*
          getblk((u16)ip->i_block[i], buf2);
          gp = (GD *)buf2;
          dp = (DIR *)buf2;
          prints(dp->name);
          prints(" i = "); putc(i + '0'); prints("\n\r");
          dp = (DIR *)((char *)dp + dp->rec_len);
          */
        }
    }
}  

int prints(char *s)
{
  while(*s)
    {
      putc(*s++);
    }
}

int gets(char *s)
{
  while((*s = getc()) != '\r')
    {
      putc(*s++);
    }
  *s = 0;
}

int getblk(u16 blk, char *buf)
{
  // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
  readfd( blk/18, ((blk)%18)/9, ( ((blk)%18)%9)<<1, buf);
}

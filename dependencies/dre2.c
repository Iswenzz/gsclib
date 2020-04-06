#include "dre2.h"

// Frequency analysis ranking.
const int dre2_frequency[RANGE] = {
   0,   1,  69, 136, 139, 140, 141, 142,
 143, 144, 241,   2,   3, 245,   8,  15,
  26,  37,  47,  58,  70,  81,  92, 103,
 114, 125, 132, 133, 134, 135, 137, 138,
 255, 206, 226, 152, 176, 154, 183, 224,
 192, 191, 175, 158, 233, 228, 231, 172,
 197, 196, 189, 186, 182, 187, 184, 181,
 190, 185, 201, 222, 167, 161, 168, 204,
 159, 223, 214, 218, 207, 216, 202, 203,
 221, 227, 198, 193, 210, 219, 213, 212,
 208, 177, 211, 220, 225, 195, 194, 217,
 188, 200, 174, 179, 149, 180, 164, 178,
 162, 252, 232, 238, 244, 254, 237, 236,
 247, 249, 209, 229, 243, 240, 250, 251,
 234, 205, 246, 248, 253, 242, 230, 239,
 215, 235, 199, 165, 171, 166, 145,   4,
 146,   5, 169, 157,   6, 150,   7, 163,
 151, 173, 170, 160, 153,   9,  10,  11,
 155, 147,  12, 156,  13,  14,  16,  17,
  18,  19,  20,  21,  22,  23,  24,  25,
  27,  28,  29,  30,  31,  32,  33,  34,
  35,  36,  38, 148,  39,  40,  41,  42,
  43,  44,  45,  46,  48,  49,  50,  51,
  52,  53,  54,  55,  56,  57,  59,  60,
  61,  62,  63,  64,  65,  66,  67,  68,
  71,  72,  73,  74,  75,  76,  77,  78,
  79,  80,  82,  83,  84,  85,  86,  87,
  88,  89,  90,  91,  93,  94,  95,  96,
  97,  98,  99, 100, 101, 102, 104, 105,
 106, 107, 108, 109, 110, 111, 112, 113,
 115, 116, 117, 118, 119, 120, 121, 122,
 123, 124, 126, 127, 128, 129, 130, 131
};

const int dre2_predefined_classes[11][256] = {
  // Alphas.
  {
   'a','b','c','d','e','f','g','h','i','j',
   'k','l','m','n','o','p','q','r','s','t',
   'u','v','w','x','y','z','A','B','C','D',
   'E','F','G','H','I','J','K','L','M','N',
   'O','P','Q','R','S','T','U','V','W','X',
   'Y','Z', -1,
  },

  // Not-alphanumeric or '-'
  {
     0, 1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 46, 47, 58, 59, 60,
    61, 62, 63, 64, 91, 92, 93, 94, 95, 96,
   123,124,125,126,127,128,129,130,131,132,
   133,134,135,136,137,138,139,140,141,142,
   143,144,145,146,147,148,149,150,151,152,
   153,154,155,156,157,158,159,160,161,162,
   163,164,165,166,167,168,169,170,171,172,
   173,174,175,176,177,178,179,180,181,182,
   183,184,185,186,187,188,189,190,191,192,
   193,194,195,196,197,198,199,200,201,202,
   203,204,205,206,207,208,209,210,211,212,
   213,214,215,216,217,218,219,220,221,222,
   223,224,225,226,227,228,229,230,231,232,
   233,234,235,236,237,238,239,240,241,242,
   243,244,245,246,247,248,249,250,251,252,
   253,254,255,-1
  },

  // Digit.
  {
   '0','1','2','3','4','5','6','7','8','9',
    -1
  },

  // Digits, including 8-bit obfuscation digits.
  {
   '0','1','2','3','4','5','6','7','8','9',
   215,225,226,231,238,239,247,250,254,-1
  },

  // 8-bit obfuscation digits.
  {
   215,225,226,231,238,239,247,250,254,-1
  },

  // Hex characters.
  {
   'a','b','c','d','e','f','A','B','C','D',
   'E','F','0','1','2','3','4','5','6','7',
   '8','9',-1
  },

  // URL characters.
  {
   'a','b','c','d','e','f','g','h','i','j',
   'k','l','m','n','o','p','q','r','s','t',
   'u','v','w','x','y','z','A','B','C','D',
   'E','F','G','H','I','J','K','L','M','N',
   'O','P','Q','R','S','T','U','V','W','X',
   'Y','Z','0','1','2','3','4','5','6','7',
   '8','9','-','.','/',':','_','@',-1
  },

  // Domain chars.
  {
   'a','b','c','d','e','f','g','h','i','j',
   'k','l','m','n','o','p','q','r','s','t',
   'u','v','w','x','y','z','A','B','C','D',
   'E','F','G','H','I','J','K','L','M','N',
   'O','P','Q','R','S','T','U','V','W','X',
   'Y','Z','0','1','2','3','4','5','6','7',
   '8','9','-','.',-1
  },

  // Word chars.
  {
   'a','b','c','d','e','f','g','h','i','j',
   'k','l','m','n','o','p','q','r','s','t',
   'u','v','w','x','y','z','A','B','C','D',
   'E','F','G','H','I','J','K','L','M','N',
   'O','P','Q','R','S','T','U','V','W','X',
   'Y','Z','0','1','2','3','4','5','6','7',
   '8','9','-',-1
  },

  // White space.
  {
   ' ','\t','\n','\r','\f',-1
  },

  // 8 bit.
  {
   128,129,130,131,132,133,134,135,136,137,
   138,139,140,141,142,143,144,145,146,147,
   148,149,150,151,152,153,154,155,156,157,
   158,159,160,161,162,163,164,165,166,167,
   168,169,170,171,172,173,174,175,176,177,
   178,179,180,181,182,183,184,185,186,187,
   188,189,190,191,192,193,194,195,196,197,
   198,199,200,201,202,203,204,205,206,207,
   208,209,210,211,212,213,214,215,216,217,
   218,219,220,221,222,223,224,225,226,227,
   228,229,230,231,232,233,234,235,236,237,
   238,239,240,241,242,243,244,245,246,247,
   248,249,250,251,252,253,254,255,-1
  }
};

// Create an escaped string, optionally with skip-matching.
unsigned char *dre2_escaped( unsigned char *re, int skip_match )
{
  unsigned char *buffer, *escaped, *ptr;
  int length;

  length = strlen( re );
  if ( skip_match )
    length = length * 4 + 1;
  else
    length = length * 2 + 1;

  escaped = ( unsigned char * )calloc( length, sizeof( unsigned char ) );
  buffer = escaped;

  ptr = re;
  while ( *ptr )
  {
    switch ( *ptr )
    {
      case '^':
      case '$':
      case '(':
      case ')':
      case '\\':
      case '.':
      case '*':
      case '+':
      case '{':
      case '}':
      case '[':
      case ']':
      case '|':
        *buffer++ = '\\';
        *buffer++ = *ptr;
        break;
      case '?':
        *buffer++ = '.';
        break;
      default:
        *buffer++ = *ptr;
    }
    if ( skip_match )
    {
       *buffer++ = '.';
       *buffer++ = '?';
    }
    *ptr++;
  }
  *buffer = '\0';
  return escaped;
}

// Determine if a sorted array contains an item.
int dre2_binsearch( int *values, int min, int max, int key )
{
  int mid;

  if ( max < min )
    return false;
  mid = ( min + max ) / 2;
  if ( values[mid] > key )
    return dre2_binsearch( values, min, mid - 1, key );
  else if ( values[mid] < key )
    return dre2_binsearch( values, mid + 1, max, key );
  else
    return true;
}

// Determine the largest element of an array.
int dre2_largest( int *values, int length )
{
  int i, largest, index;
  largest = -1;
  for ( i = 0; i < length; i++ )
  {
    if ( largest < values[i] )
    {
      largest = values[i];
      index = i;
    }
  }
  return index;
}

// Determine if an array contains an item.
int dre2_contains_int( int *values, int length, int key )
{
  int i;
  for ( i = 0; i < length; i++ )
  {
    if ( values[i] == key )
      return i + 1;
  }
  return false;
}

// Determine if a string contains a character.
int dre2_contains_char( unsigned char *string, unsigned char c )
{
  unsigned char *pch;
  int length;

  length = strlen( string );
  pch = ( unsigned char * )memchr( string, c, length );
  if ( pch != NULL && pch - string <= length )
    return true;
  return false;
}

// Predefined character classes, e.g. \a, \d, \s, etc.
void dre2_predefined_class( struct dre2_node *node, unsigned char *c, int action, int part_of_class )
{
  int i, index;
  if ( !part_of_class )
  {
    free( node->possible );
    node->possible = NULL;
    switch ( *c )
    {
      case 'a':
        node->c = DRE2_ALPHA;
        break;
      case 'b':
        node->c = DRE2_BORDER;
        break;
      case 'd':
        node->c = DRE2_DIGIT;
        break;
      case 'e':
        node->c = DRE2_SIM_DIGIT;
        break;
      case 'f':
        node->c = DRE2_OBF_DIGIT;
        break;
      case 'h':
        node->c = DRE2_HEX;
        break;
      case 'u':
        node->c = DRE2_URL;
        break;
      case 'v':
        node->c = DRE2_DOMAIN;
        break;
      case 'w':
        node->c = DRE2_WORD;
        break;
      case 's': 
        node->c = DRE2_WHITE_SPACE;
        break;
      case '8':
        node->c = DRE2_8BIT;
        break;
      case 'n':
        node->c = '\n';
        break;
      case 'r':
        node->c = '\r';
        break;
      case 't':
        node->c = '\t';
        break;
      case 'z':
        node->c = DRE2_EOF;
        break;
      default:
        node->c = *c;
        break;
    }
  } else
  {
    switch ( *c )
    {
      case 'a':
        index = 0;
      case 'b':
        index = 1;
      case 'd':
        index = 2;
      case 'e':
        index = 3;
      case 'f':
        index = 4;
      case 'h':
        index = 5;
      case 'u':
        index = 6;
      case 'v':
        index = 7;
      case 'w':
        index = 8;
      case 's':
        index = 9;
      case '8':
        index = 10;
        // Go through the array.
        i = 0;
        while ( dre2_predefined_classes[index][i] != -1 )
        {
          node->possible[dre2_predefined_classes[index][i]] = action;
          i++;
        }
        break;
      case 'n':
        node->possible['\n'] = action;
        break;
      case 'r':
        node->possible['\r'] = action;
        break;
      case 't':
        node->possible['\t'] = action;
        break;
      default:
        node->possible[*c] = action;
        break;
    }
  }
}

// Evaluate a character class.
int dre2_character_class( struct dre2_node *node, unsigned char *re, int s )
{
  int length = strlen(re);
  int i = s;
  int action;
  int k;

  if ( re[i] == ']' )
  {
    printf( "No content in charcter class.\n" );
    return false;
  } else if ( re[i] == '^' )
  {
    i++;
    action = false;
  } else
  {
    action = true;
  }

  for ( k = 0; k < RANGE; k++ )
    node->possible[k] = action == true ? false : true;
  node->possible[0] = false;

  unsigned char c;
  unsigned char last = '\0';
  while ( i < length )
  {
    c = re[i];
    if ( c == '\\' )
    {
      i++;
      if ( i == length )
      {
        printf( "Invalid character class.\n" );
        return false;
      }
      c = re[i];
      dre2_predefined_class( node, &c, action, true );
      last = '\0';
      i++;
      continue;
    } else if ( c == '-' )
    {
      i++;
      if ( i == length )
      {
        printf( "Invalid character class.\n" );
        return false;
      }
      c = re[i];
      if ( c == ']' )
      {
        node->possible['-'] = action;
        return i;
      } else
      {
        if ( !last || last > c )
        {
          printf( "Invalid range in character class.\n" );
          return false;
        }
        for ( k = last; k <= c; k++ )
          node->possible[k] = action;
      }
      i++;
      continue;
    } else if ( c == ']' )
    {
      return i;
    } else
    {
      node->possible[c] = action;
    }
    i++;
    last = c;
  }
  return false;
}

// Convert a string into an integer.
int string_to_int( unsigned char *s )
{
  // Number of digits in the string.
  int d = strlen( s );

  // Multiplier.
  int m = 1;

  // Iterator.
  int i;

  // Check for null
  if ( !s || !*s ) {
    return 0;
  }

  // Check for infinite
  if ( s[0] == '+' )
  {
    return DRE2_INFINITE;
  }

  // Find out the max multiplier.
  for ( i = 0; i < d; i++ )
    m *= 10;
  m /= 10;

  // Convert it to an int.
  int ret = 0;
  for ( i = 0; i < d; i++ )
  {
    ret += ( s[i] - '0' ) * m;
    m /= 10;
  }
  return ret;
}


// Exact size or size range, e.g. {0,4}, {2,}, {3}
struct dre2_range_return dre2_range( unsigned char *re, int length, int pos )
{
  unsigned char *min_buffer, *max_buffer;
  min_buffer = ( unsigned char * )calloc( 5, sizeof( unsigned char ) );
  max_buffer = ( unsigned char * )calloc( 5, sizeof( unsigned char ) );

  pos++;

  int t = pos;

  // Is this modifier valid?
  int valid = true;
  // Are we still working on the first part of the range?
  int w_min = true;
  // Number of characters in the min string.
  int cmin = 0;
  // Number of characters in the max string.
  int cmax = 0;

  unsigned char c;
  while ( pos < length )
  {
    c = re[pos];
    if ( c == ',' )
    {
      if ( t == pos )
      {
        valid = false;
        break;
      }
      if ( !w_min )
      {
        valid = false;
        break;
      }
      w_min = false;
    } else if ( c == '}' )
    {
      break;
    } else if ( c < '0' || c > '9' )
    {
      valid = false;
      break;
    } else
    {
      int j;
      if ( w_min )
      {
        cmin++;
        min_buffer[cmin - 1] = c;
      } else
      {
        cmax++;
        max_buffer[cmax - 1] = c;
      }
    }
    pos++;
  }
  if ( !w_min )
  {
    // See if it's unbounded on the right, e.g. {1,}
    if ( cmax == false )
    {
      max_buffer[0] = '+';
    }
  } else
  {
    // See if it's an exact size, e.g. {3}
    strcat( max_buffer, min_buffer );
  }

  // Setup the return structure.
  struct dre2_range_return ret;
  ret.min = DRE2_INFINITE;
  ret.max = DRE2_INFINITE;
  ret.pos = DRE2_INFINITE;
  ret.valid = false;

  // Make sure it's valid.
  if ( !valid )
  {
    printf( "Invalid range {}\n" );
    return ret;
  }

  // Convert strings to integers.
  int min = string_to_int( min_buffer );
  int max = string_to_int( max_buffer );

  // Make sure it's a valid size range.
  if ( min > max && max != DRE2_INFINITE )
  {
    printf("Invalid range, min is greater than max!\n");
    return ret;
  }
  if ( min > 100 || max > 100 )
  {
    printf( "Way too high of a range, use + or *.\n" );
    return ret;
  }

  // Free buffers.
  free( min_buffer );
  free( max_buffer );
  min_buffer = NULL;
  max_buffer = NULL;

  // Setup the return structure and return it.
  ret.min = min;
  ret.max = max;
  ret.pos = pos;
  ret.valid = true;
  return ret;
}

// Clean up memory, etc.
void cleanup_nodes( struct dre2_node **v, int node_count )
{
  int i;
  if ( *v != NULL )
  {
    for ( i = 0; i < node_count; i++ )
    {
      if ( ( *v )[i].n != NULL )
      {
        free( ( *v )[i].n );
        ( *v )[i].n = NULL;
      }
      if ( ( *v )[i].p != NULL )
      {
        free( ( *v )[i].p );
        ( *v )[i].p = NULL;
      }
      if ( ( *v )[i].c == DRE2_CHAR_CLASS )
      {
        free( ( *v )[i].possible );
        ( *v )[i].possible = NULL;
      }
      if ( ( *v )[i].min_n != NULL )
      {
        free( ( *v )[i].min_n );
        ( *v )[i].min_n = NULL;
      }
    }
    free( *v );
    *v = NULL;
  }
}

// Clean up memory, etc.
void cleanup_dre2( struct dre2 *graph )
{
  cleanup_nodes( &graph->v, graph->count );
  free( graph->v ); graph->v = NULL;
  if ( graph->starting_points != NULL ) { free( graph->starting_points ); graph->starting_points = NULL; }
  if ( graph->starting_chars != NULL ) { free( graph->starting_chars ); graph->starting_chars = NULL; }
  if ( graph->r_temp != NULL ) { free( graph->r_temp ); graph->r_temp = NULL; }
  if ( graph->reachable != NULL ) { free( graph->reachable ); graph->reachable = NULL; }
  if ( graph->state != NULL ) { free( graph->state ); graph->state = NULL; }
  if ( graph->original != NULL ) { cleanup_dre2( graph->original ); }
  free( graph );
  graph = NULL;
}

int dre2_find_paths_recursive( struct dre2 *graph, int id, int *path_count, struct dre2_path **paths )
{
  int i, j;
  int size, last;
  struct dre2_path *path, *next_path;

  if ( *path_count >= 1024 )
  {
    for ( i = 0; i < *path_count; i++ )
    {
      if ( ( *paths )[i].nodes != NULL )
      {
        free( ( *paths )[i].nodes );
        ( *paths )[i].nodes = NULL;
      }
    }
    free( *paths );
    *paths = NULL;
    *path_count = 0;
    return false;
  }

  size = ( *paths )[id].count;
  last = ( *paths )[id].nodes[( *paths )[id].count - 1];

  for ( i = 0; i < graph->v[last].min_n_count; i++ )
  {
    path = &( *paths )[id];
    if ( i == 0 )
    {
      // For the first possible node, just add it to the current path.
      ( *paths )[id].count++;
      ( *paths )[id].nodes[( *paths )[id].count - 1] = graph->v[last].min_n[i];
      if ( dre2_find_paths_recursive( graph, id, path_count, paths ) == false )
        return false;
    } else
    {
      // For the other nodes, split the path.
      *path_count = *path_count + 1;
      *paths = ( struct dre2_path * )realloc( *paths, sizeof( struct dre2_path ) * *path_count );
      next_path = &( *paths )[*path_count - 1];
      next_path->count = size + 1;
      next_path->nodes = ( int * )malloc( sizeof( int ) * graph->count );

      // Copy the previous nodes and add the current one.
      for ( j = 0; j < size; j++ )
        next_path->nodes[j] = ( *paths )[id].nodes[j];
      next_path->nodes[size] = graph->v[last].min_n[i];
      if ( dre2_find_paths_recursive( graph, *path_count - 1, path_count, paths ) == false )
        return false;
    }
  }
  return true;
}

// Frequency/cost of a single node.
int dre2_node_cost( struct dre2 *graph, int id )
{
  int i, j;
  int index;
  int cost;
  struct dre2_node *node;

  node = &graph->v[id];
  cost = 0;
  if ( node->c >= 0 )
  {
    return dre2_frequency[node->c];
  } else if ( node->c >= DRE2_8BIT && node->c <= DRE2_ALPHA )
  {
    index = node->c * -1 - 5;
    i = 0;
    while ( dre2_predefined_classes[index][i] != -1 )
    {
      cost += dre2_frequency[dre2_predefined_classes[index][i]];
      i++;
    }
    return cost;
  } else
  {
    if ( node->c == DRE2_DOT )
    {
      for ( i = 0; i < RANGE; i++ )
        cost += dre2_frequency[i];
      return cost;
    } else if ( node->c == DRE2_CHAR_CLASS )
    {
      for ( i = 0; i < RANGE; i++ )
      {
        if ( node->possible[i] )
          cost += dre2_frequency[i];
      }
      return cost;
    } else
    {
      return RANGE * RANGE;
    }
  }
}

// Pick the best node that is required.
int dre2_best_choice( struct dre2 *graph, int *required, int count )
{
  int i, j;
  int temp;
  int *ids, *cost;
  int best;
  int literal;

  ids = ( int * )malloc( sizeof( int ) * count );
  cost = ( int * )malloc( sizeof( int ) * count );

  literal = false;
  for ( i = 0; i < count; i++ )
  {
    ids[i] = required[i];
    cost[i] = required[i] == 0 || required[i] == graph->count - 1 ? 100000 : dre2_node_cost( graph, required[i] );
    if ( graph->v[required[i]].c >= 0 )
      literal = true;
  }

  for ( i = 0; i < count - 1; i++ )
  {
    for ( j = i + 1; j < count; j++ )
    {
      if ( cost[i] > cost[j] || ( cost[i] == cost[j] && ids[i] < ids[j] ) )
      {
        temp = cost[i];
        cost[i] = cost[j];
        cost[j] = temp;
        temp = ids[i];
        ids[i] = ids[j];
        ids[j] = temp;
      }
    }
  }
  best = ids[0];

  if ( graph->options & DRE2_GREEDY && !literal && dre2_contains_int( required, count, graph->count - 2 ) )
    best = graph->count - 2;

  free( cost );
  free( ids );
  cost = NULL;
  ids = NULL;

  return best;
}

// Set starting chars for multiple nodes.
void dre2_set_chars( struct dre2 *graph, int id )
{
  int i, iter;
  int index;
  struct dre2_node *node;

  node = &graph->v[id];
  if ( node->c >= 0 )
  {
    graph->starting_chars[node->c] = true;
    if ( graph->options & DRE2_NO_CASE )
    {
      if ( node->c >= 'a' && node->c <= 'z' )
        graph->starting_chars[node->c - ( 'a' - 'A' )] = true;
      else if ( node->c >= 'A' && node->c <= 'Z' )
        graph->starting_chars[node->c + ( 'a' - 'A' )] = true;
    }
  } else if ( node->c == DRE2_CHAR_CLASS )
  {
    for ( i = 0; i < RANGE; i++ )
    {
      if ( node->possible[i] )
      {
        graph->starting_chars[i] = true;
        if ( graph->options & DRE2_NO_CASE )
        {
          if ( i >= 'a' && i <= 'z' )
            graph->starting_chars[i - ( 'a' - 'A' )] = true;
          else if ( i >= 'A' && i <= 'Z' )
            graph->starting_chars[i + ( 'a' - 'A' )] = true;
        }
      }
    }
  } else if ( node->c == DRE2_DOT )
  {
    for ( i = 0; i < RANGE; i++ )
      graph->starting_chars[i] = true;
  } else if ( node->c >= DRE2_8BIT && node->c <= DRE2_ALPHA )
  {
    index = node->c * -1 - 5;
    i = 0;
    while ( dre2_predefined_classes[index][i] != -1 )
    {
      graph->starting_chars[dre2_predefined_classes[index][i]] = true;
      if ( graph->options & DRE2_NO_CASE )
      {
        if ( dre2_predefined_classes[index][i] >= 'a' && dre2_predefined_classes[index][i] <= 'z' )
          graph->starting_chars[dre2_predefined_classes[index][i] - ( 'a' - 'A' )] = true;
        else if ( dre2_predefined_classes[index][i] >= 'A' && dre2_predefined_classes[index][i] <= 'Z' )
          graph->starting_chars[dre2_predefined_classes[index][i] + ( 'a' - 'A' )] = true;
      }
      i++;
    }
  }
}

// Set the starting chars.
void dre2_starting_chars( struct dre2 *graph, int *minimal )
{
  int i, count;
  struct dre2_node *node;

  for ( i = 0; i < RANGE; i++ )
    graph->starting_chars[i] = false;

  if ( graph->starting_point == graph->count - 1 && graph->v[graph->count - 1].n_count > 0 && ( graph->options & DRE2_GREEDY ) )
    graph->starting_point = 0;

  if ( graph->starting_point == -1 )
  {
    // Using multiple nodes.
    for ( i = 0; i < graph->starting_count; i++ )
      dre2_set_chars( graph, graph->starting_points[i] );
  } else if ( graph->starting_point != 0 && graph->starting_point != graph->count - 1 )
  {
    // Only a single node, set the chars for that node.
    dre2_set_chars( graph, graph->starting_point );
  } else if ( graph->starting_point == 0 )
  {
    // Set all of the chars possible from the reachable nodes of the first node.
    for ( i = 0; i < graph->v[0].n_count; i++ )
    {
      if ( minimal[graph->v[0].n[i]] || ( graph->options & DRE2_GREEDY ) )
        dre2_set_chars( graph, graph->v[0].n[i] );
    }
  } else
  {
    // Set all of the chars possible from the parents of the last node.
    for ( i = 0; i < graph->v[graph->count - 1].p_count; i++ )
    {
      if ( minimal[graph->v[graph->count - 1].p[i]] || ( graph->options & DRE2_GREEDY ) )
        dre2_set_chars( graph, graph->v[graph->count - 1].p[i] );
    }
  }

  // Check if the there is a single starting char or multiple (determines matching method)
  count = 0;
  for ( i = 0; i < RANGE; i++ )
  {
    if ( graph->starting_chars[i] )
      count++;
    if ( count > 1 )
      break;
  }
  if ( count > 1 )
    graph->single = false;
  else
    graph->single = true;
}

// Find the best starting node in the graph.
int dre2_starting_point( struct dre2 *graph, int *minimal, int *minimal_id, int minimal_count )
{
  int i, j, k, l, m;
  int min_iter, iter;
  int id, all, found, temp;
  int *required;
  int required_count;
  int best;
  int **found_in, *found_in_count, *found_in_id;
  int *swapper;
  int *remaining;
  int largest, last_largest;
  struct dre2_path *paths;
  int path_count;
  struct dre2_fl_cost cost;

  // First, check if the first or last node is acceptable.
  cost = dre2_first_or_last_cost( graph, minimal );

  // Initialize paths.
  path_count = 1;
  paths = ( struct dre2_path * )malloc( sizeof( struct dre2_path ) );
  paths[0].nodes = ( int * )malloc( sizeof( int ) * graph->count );
  paths[0].count = 1;
  paths[0].nodes[0] = 0;

  graph->starting_points = ( int * )malloc( sizeof( int ) * graph->count );
  graph->starting_count = 0;

  // Recursively find paths through the minimal graph.
  dre2_find_paths_recursive( graph, 0, &path_count, &paths );
  required = NULL;
  for ( i = 0; i < path_count; i++ )
  {
    best = dre2_best_choice( graph, paths[i].nodes, paths[i].count );
    if ( !dre2_contains_int( graph->starting_points, graph->starting_count, best ) )
      graph->starting_points[graph->starting_count++] = best;
  }

  // Allocate some memory.
  found_in = ( int ** )malloc( sizeof( int * ) * ( minimal_count - 2 ) );
  found_in_count = ( int * )malloc( sizeof( int ) * ( minimal_count - 2 ) );
  found_in_id = ( int * )malloc( sizeof( int ) * ( minimal_count - 2 ) );
  remaining = ( int * )malloc( sizeof( int ) * ( minimal_count - 2 ) );

  for ( i = 0; i < minimal_count - 2; i++ )
  {
    found_in_count[i] = 0;
    found_in[i] = ( int * )malloc( sizeof( int ) * path_count );
    found_in_id[i] = minimal_id[i + 1];
  }

  best = -1;
  if ( path_count == 1 && paths[0].count > 2 )
  {
    required_count = 0;
    required = ( int * )malloc( sizeof( int ) * graph->count );
    for ( i = 1; i < paths[0].count -1; i++ )
    {
      switch ( graph->v[paths[0].nodes[i]].c )
      {
        case DRE2_BOL:
        case DRE2_EOL:
        case DRE2_EOF:
          break;
        default:
          required[required_count++] = paths[0].nodes[i];
          break;
      }
    }
    if ( required_count > 0 )
      best = dre2_best_choice( graph, required, required_count );
    goto INITIAL_CLEANUP;
  } else if ( path_count > 1 )
  {
    required_count = 0;
    required = ( int * )malloc( sizeof( int ) * graph->count );
    for ( i = 1; i < minimal_count - 1; i++ )
    {
      all = true;
      id = minimal_id[i];
      switch ( graph->v[id].c )
      {
        case DRE2_BOL:
        case DRE2_EOL:
        case DRE2_EOF:
          break;
        default:
          for ( j = 0; j < path_count; j++ )
          {
            if ( !dre2_binsearch( paths[j].nodes, 0, paths[j].count - 1, id ) )
            {
              all = false;
            } else
            {
              found_in_count[i - 1]++;
              found_in[i - 1][found_in_count[i - 1] - 1] = j;
            }
          }
          if ( all )
            required[required_count++] = id;
          break;
      }
    }
    if ( required_count > 0 )
    {
      best = dre2_best_choice( graph, required, required_count );
      goto INITIAL_CLEANUP;
    }
  }

  best = dre2_first_or_last( graph, &cost );

  INITIAL_CLEANUP:
  if ( path_count > 1 && dre2_use_paths( graph, best, &cost ) )
    best = -1;

  if ( required != NULL )
  {
    free( required ); required = NULL;
  }

  for ( i = 0; i < path_count; i++ )
  {
    free( paths[i].nodes );
    paths[i].nodes = NULL;
  }
  for ( i = 0; i < minimal_count - 2; i++ )
  {
    free( found_in[i] ); found_in[i] = NULL;
  }
  free( found_in ); found_in = NULL;
  free( found_in_count ); found_in_count = NULL;
  free( found_in_id ); found_in_id = NULL;
  free( remaining ); remaining = NULL;
  free( paths ); paths = NULL;

  return best;
}

// Find all of the reachable nodes from a node excluded backlinks.
void dre2_min_reachable( struct dre2 *graph, int **reachable, int **visited, int id )
{
  if ( ( *visited )[id] == true )
    return;
  ( *visited )[id] = true;

  int i;
  for ( i = 0; i < graph->v[id].n_count; i++ )
  {
    if ( id < graph->v[id].n[i] )
    {
      struct dre2_node *neighbor = &graph->v[graph->v[id].n[i]];
      if ( neighbor->c == DRE2_GROUP_OPEN || neighbor->c == DRE2_GROUP_CLOSE )
      {
        if ( graph->v[id].n[i] == graph->count - 1 )
          ( *reachable )[graph->v[id].n[i]] = true;
        dre2_min_reachable( graph, reachable, visited, graph->v[id].n[i] );
      } else
      {
        ( *reachable )[graph->v[id].n[i]] = true;
      }
    }
  }
}

// Find all of the reachable nodes from a node.
void dre2_reachable( struct dre2 *graph, int **reachable, int **visited, int id )
{
  if ( ( *visited )[id] == true )
    return;
  ( *visited )[id] = true;

  int i;
  for ( i = 0; i < graph->v[id].n_count; i++ )
  {
    struct dre2_node *neighbor = &graph->v[graph->v[id].n[i]];

    // If it's a group node, check neighbors.
    if ( neighbor->c == DRE2_GROUP_OPEN || neighbor->c == DRE2_GROUP_CLOSE )
    {
      if ( graph->v[id].n[i] == graph->count - 1 )
        ( *reachable )[graph->v[id].n[i]] = true;
      dre2_reachable( graph, reachable, visited, graph->v[id].n[i] );
    } else
    {
      ( *reachable )[graph->v[id].n[i]] = true;
    }
  }
}

// Strip out the group open and close nodes.
void dre2_strip_groups( struct dre2 *graph, struct dre2 *new_graph, struct dre2_node **new_nodes, int *minimal, int **new_minimal, int *new_minimal_count, int **minimal_id )
{
  int i, j, k;
  struct dre2_node *nodes, *node;
  int node_count;
  int removed, offset;
  int *reachable, *visited, *temp_minimal;
  int *min_reachable, *min_visited;

  // Allocate some memory.
  reachable = ( int * )malloc( sizeof( int ) * graph->count );
  visited = ( int * )malloc( sizeof( int ) * graph->count );
  temp_minimal = ( int * )malloc( sizeof( int ) );
  min_reachable = ( int * )malloc( sizeof( int ) * graph->count );
  min_visited = ( int * )malloc( sizeof( int ) * graph->count );

  for ( i = 0; i < graph->count; i++ )
    ( *new_minimal )[i] = false;

  node_count = 0;
  *new_minimal_count = 0;
  for ( i = 0; i < graph->count; i++ )
  {
    // Initialize reachable nodes to all false.
    for ( j = 0; j < graph->count; j++ )
    {
      reachable[j] = false;
      visited[j] = false;
      min_reachable[j] = false;
      min_visited[j] = false;
    }
    dre2_reachable( graph, &reachable, &visited, i );
    dre2_min_reachable( graph, &min_reachable, &min_visited, i );

    if ( ( graph->v[i].c != DRE2_GROUP_OPEN && graph->v[i].c != DRE2_GROUP_CLOSE ) || ( i == 0 || i == graph->count - 1 ) )
    {
      // Add node to our min tree.
      dre2_add_node( new_nodes, &node_count, graph->v[i].c, &temp_minimal, true );

      ( *new_nodes )[node_count - 1].min_n_count = 0;
      ( *new_nodes )[node_count - 1].min_n = NULL;
      if ( minimal[i] )
      {
        ( *new_minimal )[node_count - 1] = true;
        *new_minimal_count = *new_minimal_count + 1;
        ( *minimal_id )[*new_minimal_count - 1] = node_count - 1;
      }
      graph->v[i].min_id = node_count - 1;
      if ( graph->v[i].c == DRE2_CHAR_CLASS )
      {
        for ( j = 0; j < RANGE; j++ )
          ( *new_nodes )[node_count - 1].possible[j] = graph->v[i].possible[j];
      }

      // Find the reachable nodes.
      for ( j = 0; j < graph->count; j++ )
      {
        if ( reachable[j] )
          dre2_add_neighbor( new_nodes, node_count - 1, j );
        if ( min_reachable[j] && minimal[j] )
        {
          ( *new_nodes )[node_count - 1].min_n_count++;
          if ( ( *new_nodes )[node_count - 1].min_n == NULL )
            ( *new_nodes )[node_count - 1].min_n = ( int * )malloc( sizeof( int ) * graph->count );
          ( *new_nodes )[node_count - 1].min_n[( *new_nodes )[node_count - 1].min_n_count - 1] = j;
        }
      }
    }
  }

  // Update the node IDs.
  for ( i = 0; i < node_count; i++ )
  {
    for ( j = 0; j < ( *new_nodes )[i].n_count; j++ )
      ( *new_nodes )[i].n[j] = graph->v[( *new_nodes )[i].n[j]].min_id;
  }

  for ( i = 0; i < *new_minimal_count; i++ )
  {
    for ( j = 0; j < ( *new_nodes )[( *minimal_id )[i]].min_n_count; j++ )
      ( *new_nodes )[( *minimal_id )[i]].min_n[j] = graph->v[( *new_nodes )[( *minimal_id )[i]].min_n[j]].min_id;
  }

  // Setup the minimized graph.
  new_graph->count = node_count;

  // Free the temp reachable nodes array.
  free( reachable );
  free( visited );
  free( temp_minimal );
  free( min_reachable );
  free( min_visited );

  // Set them all to null.
  reachable = NULL;
  visited = NULL;
  temp_minimal = NULL;
  min_reachable = NULL;
  min_visited = NULL;
}

// Find out the cost of a single node.
struct dre2_cost dre2_single_cost( struct dre2 *graph, int id )
{
  int i, j;
  int c_count, frequency;
  unsigned char *temp;
  int *tp, *original;
  struct dre2_cost cost;

  temp = ( unsigned char * )calloc( RANGE, sizeof( unsigned char ) );
  tp = ( int * )calloc( RANGE, sizeof( int ) );

  original = graph->starting_chars;
  graph->starting_chars = tp;

  for ( i = 0; i < RANGE; i++ )
    tp[i] = false;
  graph->starting_chars = tp;

  dre2_set_chars( graph, id );

  c_count = 0;
  frequency = 0;
  for ( j = 1; j < RANGE; j++ )
  {
    if ( graph->starting_chars[j] && !dre2_contains_char( temp, j ) )
    {
      c_count++;
      temp[c_count - 1] = j;
      frequency += dre2_frequency[j];
    }
  }
  free( temp ); temp = NULL;
  free( tp ); tp = NULL;
  graph->starting_chars = original;
  cost.c_count = c_count;
  cost.frequency = frequency;
  return cost;
}

// Find out the cost of the first node or last node.
struct dre2_fl_cost dre2_first_or_last_cost( struct dre2 *graph, int *minimal )
{
  int i, j, k;
  int f_n_count, f_c_count, f_frequency;
  int l_n_count, l_c_count, l_frequency;
  int next_count, *next_ptr;
  struct dre2_node *node;
  struct dre2_fl_cost cost;
  unsigned char *temp;
  int *tp, *original;

  f_n_count = graph->v[0].n_count;
  f_c_count = 0;
  f_frequency = 0;

  l_n_count = graph->v[graph->count - 1].p_count;
  l_c_count = 0;
  l_frequency = 0;

  for ( i = 0; i < graph->v[0].n_count; i++ )
  {
    if ( !minimal[graph->v[0].n[i]] && !( graph->options & DRE2_GREEDY ) && graph->count > 3 )
      f_n_count--;
  }
  for ( i = 0; i < graph->v[graph->count - 1].p_count; i++ )
  {
    if ( !minimal[graph->v[graph->count - 1].p[i]] && !( graph->options & DRE2_GREEDY ) && graph->count > 3 )
      l_n_count--;
  }

  // Get number of possible chars in the first reachable nodes.
  tp = ( int * )malloc( sizeof( int ) * RANGE );
  temp = ( unsigned char * )malloc( sizeof( unsigned char ) * RANGE );

  original = graph->starting_chars;
  for ( k = 0; k < 2; k++ )
  {
    graph->starting_chars = tp;
    for ( i = 0; i < RANGE; i++ )
    {
      tp[i] = false;
      temp[i] = '\0';
    }

    if ( k == 0 )
    {
      next_count = graph->v[0].n_count;
      next_ptr = graph->v[0].n;
    } else
    {
      next_count = graph->v[graph->count - 1].p_count;
      next_ptr = graph->v[graph->count - 1].p;
    }
    for ( i = 0; i < next_count; i++ )
    {
      if ( !minimal[next_ptr[i]] && !( graph->options & DRE2_GREEDY ) && graph->count > 3 )
        continue;
      dre2_set_chars( graph, next_ptr[i] );
      for ( j = 1; j < RANGE; j++ )
      {
        if ( tp[j] && !dre2_contains_char( temp, j ) )
        {
          if ( k == 0 )
          {
            f_c_count++;
            temp[f_c_count - 1] = j;
            f_frequency += dre2_frequency[j];
          } else
          {
            l_c_count++;
            temp[l_c_count - 1] = j;
            l_frequency += dre2_frequency[j];
          }
        } else
        {
        }
      }
    }
  }
  free( temp ); temp = NULL;
  free( tp ); tp = NULL;
  graph->starting_chars = original;

  cost.f_n_count = f_n_count;
  cost.f_c_count = f_c_count;
  cost.f_frequency = f_frequency;
  cost.l_n_count = l_n_count;
  cost.l_c_count = l_c_count;
  cost.l_frequency = l_frequency;

  return cost;
}

// See if the first or last node is better.
int dre2_first_or_last( struct dre2 *graph, struct dre2_fl_cost *cost )
{
  int i, j;
  double first, last, diff;

  first = ( double )cost->f_frequency;
  last = ( double )cost->l_frequency;
  diff = first / last;

  if ( cost->l_n_count == 1 && graph->v[graph->v[graph->count - 1].p[0]].c == DRE2_EOF )
  {
    return 0;
  } else {
    if ( cost->l_n_count * cost->l_c_count < cost->f_n_count * cost->f_c_count ||
       ( cost->l_n_count * cost->l_c_count == cost->f_n_count * cost->f_c_count && cost->l_frequency < cost->f_frequency ) ||
       ( cost->l_n_count * cost->l_c_count == cost->f_n_count * cost->f_c_count && diff >= 0.9 ) )
       return graph->count - 1;
  }
  return 0;
}

// See if it might be better to start somewhere in the middle of the graph.
int dre2_use_paths( struct dre2 *graph, int best, struct dre2_fl_cost *cost )
{
  int i, j;
  struct dre2_node *node;
  int b_n_count, b_c_count, b_frequency;
  int p_n_count, p_c_count, p_frequency;
  int *original, *tp;
  double bf, pf, diff;
  unsigned char *temp;
  struct dre2_cost node_cost;

  if ( best == 0 )
  {
    b_n_count = cost->f_n_count;
    b_c_count = cost->f_c_count;
    b_frequency = cost->f_frequency;
  } else if ( best == graph->count - 1 )
  {
    b_n_count = cost->l_n_count;
    b_c_count = cost->l_c_count;
    b_frequency = cost->l_frequency;
  } else
  {
    node_cost = dre2_single_cost( graph, best );
    b_n_count = 1;
    b_c_count = node_cost.c_count;
    b_frequency = node_cost.frequency;
  }

  temp = ( unsigned char * )calloc( RANGE, sizeof( unsigned char ) );
  tp = ( int * )calloc( RANGE, sizeof( int ) );
  original = graph->starting_chars;
  graph->starting_chars = tp;

  p_n_count = graph->starting_count;
  for ( i = 0; i < RANGE; i++ )
    tp[i] = false;
  graph->starting_chars = tp;

  p_c_count = 0;
  p_frequency = 0;
  for ( i = 0; i < graph->starting_count; i++ )
  {
    dre2_set_chars( graph, graph->starting_points[i] );
    for ( j = 1; j < RANGE; j++ )
    {
      if ( graph->starting_chars[j] && !dre2_contains_char( temp, j ) )
      {
        p_c_count++;
        temp[p_c_count - 1] = j;
        p_frequency += dre2_frequency[j];
      }
    }
  }

  graph->starting_chars = original;
  free( temp );
  temp = NULL;
  free( tp );
  tp = NULL;

  if ( b_n_count * b_c_count < p_n_count * p_c_count ||
     ( b_n_count * b_c_count == p_n_count * p_c_count && b_frequency <= p_frequency ) )
    return false;
  return true;
}

// Set the minimal bit to false.
void dre2_remove_minimal( int **minimal, int id )
{
  ( *minimal )[id] = false;
}

// Add a minimal bit.
void dre2_add_minimal( int **minimal, int *node_count )
{
  *minimal = ( int * )realloc( *minimal, sizeof( int ) * *node_count );
  ( *minimal )[*node_count - 1] = true;
}

// Add a node.
void dre2_add_node( struct dre2_node **v, int *node_count, int c, int **minimal, int no_realloc )
{
  // Initialize the node count and vertex array if necessary.
  if ( ! *node_count )
  {
    *node_count = 1;
    if ( !no_realloc )
      *v = ( struct dre2_node * )malloc( sizeof( struct dre2_node ) );
  } else
  {
    // Increment node count and allocate additional memory.
    *node_count = *node_count + 1;
    if ( !no_realloc )
      *v = ( struct dre2_node * )realloc( *v, sizeof( struct dre2_node ) * *node_count );
  }

  // Set this node's data.
  ( *v )[*node_count - 1].c = c;

  // Initialize neighbor array and count.
  ( *v )[*node_count - 1].n = ( int * )malloc( sizeof( int ) );
  ( *v )[*node_count - 1].n_count = 0;

  // Initalize the parent array and count.
  ( *v )[*node_count - 1].p = ( int * )malloc( sizeof( int ) );
  ( *v )[*node_count - 1].p_count = 0;

  // Allocate some memory for character class possible lookup list.
  if ( c == DRE2_CHAR_CLASS )
    ( *v )[*node_count - 1].possible = ( int * )calloc( RANGE, sizeof( int ) );

  // Initialize min_n to NULL.
  ( *v )[*node_count - 1].min_n = NULL;

  dre2_add_minimal( minimal, node_count );
}

// Add a node to another node's neighbors.
void dre2_add_neighbor( struct dre2_node **v, int origin, int dest )
{
  // Add the neighbor.
  ( *v )[origin].n_count++;
  ( *v )[origin].n = ( int * )realloc( ( *v )[origin].n, sizeof( int ) * ( *v )[origin].n_count );
  ( *v )[origin].n[( *v )[origin].n_count - 1] = dest;
}

// Add the parent nodes
void dre2_add_parents( struct dre2 *graph )
{
  int i, j;
  for ( i = 0; i < graph->count; i++ )
  {
    struct dre2_node *node = &graph->v[i];
    for ( j = 0; j < graph->v[i].n_count; j++ )
    {
      struct dre2_node *neighbor = &graph->v[graph->v[i].n[j]];
      neighbor->p_count++;
      neighbor->p = ( int * )realloc( neighbor->p, sizeof( int ) * neighbor->p_count );
      neighbor->p[neighbor->p_count - 1] = i;
    }
  }
}

// Find out how many characters we can skip before our starting point.
int dre2_initial_skip( struct dre2 *graph )
{
  int i, j;
  int complete;
  int *reachable, *r_temp, *swapper;
  int count, c_temp;
  int total;

  count = 0;

  reachable = ( int * )malloc( sizeof( int ) * graph->count );
  r_temp = ( int * )malloc( sizeof( int ) * graph->count );

  for ( i = 0; i < graph->v[0].n_count; i++ )
  {
    reachable[count++] = graph->v[0].n[i];
  }

  total = 0;
  complete = false;
  while ( true )
  {
    c_temp = 0;
    if ( count == 1 )
    {
      if ( ( graph->v[reachable[0]].c == DRE2_BOL ) ||
           ( graph->v[reachable[0]].c == DRE2_EOL ) ||
           ( graph->v[reachable[0]].c == DRE2_EOF ) )
        total--;
    }
    for ( i = 0; i < count; i++ )
    {
      if ( reachable[i] == graph->starting_point )
      {
        total--;
        complete = true;
        break;
      }
      for ( j = 0; j < graph->v[reachable[i]].n_count; j++ )
      {
        if ( graph->v[reachable[i]].n[j] > reachable[i] && !dre2_contains_int( r_temp, c_temp, graph->v[reachable[i]].n[j] ) )
          r_temp[c_temp++] = graph->v[reachable[i]].n[j];
      }
    }

    total++;
    if ( complete )
      break;
    count = c_temp;
    swapper = reachable;
    reachable = r_temp;
    r_temp = swapper;
  }

  free( reachable );
  free( r_temp );
  reachable = NULL;
  r_temp = NULL;

  return total;
}

// Find all impossible characters.
void dre2_impossible_chars( struct dre2 *graph )
{
  int i, j, c;
  int index;

  // Initialize all chars to possible.
  for ( i = 0; i < RANGE; i++ )
    graph->impossible[i] = true;

  // Make possible all nodes found.
  for ( i = 0; i < graph->count; i++ )
  {
    c = graph->v[i].c;
    if ( c >= 0 )
    {
      graph->impossible[c] = false;
      if ( graph->options & DRE2_NO_CASE )
      {
        if ( c >= 'a' && c <= 'z' )
          graph->impossible[c - ('a' - 'A')] = false;
        else if ( c >= 'A' && c <= 'Z' )
          graph->impossible[c + ('a' - 'A')] = false;
      }
    } else if ( c >= DRE2_8BIT && c <= DRE2_ALPHA )
    {
      index = c * -1 - 5;
      j = 0;
      while ( dre2_predefined_classes[index][j] != -1 )
      {
        graph->impossible[dre2_predefined_classes[index][j]] = false;
        j++;
      }
    } else if ( c == DRE2_DOT )
    {
      for ( j = 0; j < RANGE; j++ )
        graph->impossible[j] = false;
      break;
    } else if ( c == DRE2_CHAR_CLASS )
    {
      for ( j = 0; j < RANGE; j++ )
      {
        if ( graph->v[i].possible[j] )
        {
          graph->impossible[j] = false;
          if ( graph->options & DRE2_NO_CASE )
          {
            if ( j >= 'a' && j <= 'z' )
              graph->impossible[j - ( 'a' - 'A' )] = false;
            if ( j >= 'A' && j <= 'Z' )
              graph->impossible[j + ( 'a' - 'A' )] = false;
          }
        }
      }
    }
  }
}

// Caculate the min length.
void dre2_skip_table( struct dre2 *graph )
{
  int i, j, r;
  int iter, l_iter;
  int matched, complete, total;
  int *swapper, *visited;
  int *reachable, *state, *r_temp;
  struct dre2_node *node;

  // Allocate some memory.
  state = ( int * )malloc( sizeof( int ) * graph->count );
  reachable = ( int * )malloc( sizeof( int ) * graph->count );
  r_temp = ( int * )malloc( sizeof( int ) * graph->count );

  // Initialize some variables.
  i = 0;
  iter = 0;
  total = 0;
  complete = false;

  // Initialize the reachable states to be neighbors of the first node.
  for ( i = 0; i < graph->v[graph->count - 1].p_count; i++ )
  {
    reachable[i] = graph->v[graph->count - 1].p[i];
    if ( reachable[i] == 0 )
    {
      for ( j = 0; j < RANGE; j++ )
        graph->skip_table[j] = 1;
      graph->min_length = 0;
      return;
    }
  }
  l_iter = i;

  visited = ( int * )malloc( sizeof( int ) * graph->count );
  for ( j = 0; j < RANGE; j++ )
    graph->skip_table[j] = 0;

  // Outer loop, runs until the initial node is reachable.
  while ( true )
  {
    if ( l_iter == 0 )
      break;

    total++;
    iter = 0;

    // Iterate through all of the reachable nodes.
    for ( j = 0; j < graph->count; j++ )
    {
      visited[j] = false;
      state[j] = false;
    }
    for ( i = 0; i < l_iter; i++ )
    {
      r = reachable[i];
      node = &graph->v[r];
      if ( total > 1 )
      {

        // Setup the skip table for the current node's chars.
        if ( node->c == DRE2_CHAR_CLASS )
        {
          for ( j = 0; j < RANGE; j++ )
          {
            if ( node->possible[j] && graph->skip_table[j] > total - 1 || graph->skip_table[j] == 0 )
              graph->skip_table[j] = total - 1;
          }
        } else if ( node->c >= 0 )
        {
          if ( graph->skip_table[node->c] > total - 1 || graph->skip_table[node->c] == 0 )
            graph->skip_table[node->c] = total - 1;
        }
      }
      if ( node->c == DRE2_BOL || node->c == DRE2_EOF || node->c == DRE2_EOL )
          total--;


      // Add the current node's parents to the next reachable nodes.
      for ( j = 0; j < node->p_count; j++ )
      {
        if ( !state[node->p[j]] && !visited[node->p[j]] )
          r_temp[iter++] = node->p[j];

        visited[node->p[j]] = true;
        state[node->p[j]] = true;
      }

      // Check if the initial state was reached.
      if ( state[0] == true )
      {
        complete = true;
      }
    }
    
    l_iter = iter;

    // Change the current reachable nodes to the next reachable nodes from above.
    swapper = reachable;
    reachable = r_temp;
    r_temp = swapper;
    if ( complete )
      break;
  }

  // Set remaining character's skip table value.
  for ( i = 0; i < RANGE; i++ )
  {
    if ( graph->skip_table[i] == 0 )
      graph->skip_table[i] = total;
  }

  // Set the min length of the regular expression.
  graph->min_length = total;

  free( reachable );
  free( r_temp );
  free( state );
  free( visited );
  reachable = NULL;
  r_temp = NULL;
  state = NULL;
  visited = NULL;
}

// Duplicate a group.
void dre2_duplicate_group( struct dre2_node **v, int *node_count, int *last_node, struct dre2_parse_return *res, int **minimal )
{
  int i, j, diff;
  int o, c;

  for ( i = res->open; i <= res->close; i++ )
  {
    dre2_duplicate_node( v, node_count, i, minimal );
    ( *minimal )[*node_count - 1] = ( *minimal )[i];
    if ( i != res->open )
    {
      ( *v )[*node_count - 1].p_count = ( *v )[i].p_count;
      ( *v )[*node_count - 1].p = ( int * )malloc( sizeof( int ) * ( *v )[i].p_count );
      for ( j = 0; j < ( *v )[i].p_count; j++ )
      {
        diff = ( *v )[i].p[j] - res->open;
        ( *v )[*node_count - 1].p[j] = *last_node + diff + 1;
      }
    } else
    {
      ( *v )[*node_count - 1].p_count = 1;
      ( *v )[*node_count - 1].p = ( int * )malloc( sizeof( int ) );
      ( *v )[*node_count - 1].p[0] = res->close;
    }

    if ( i != res->close )
    {
      ( *v )[*node_count - 1].n_count = ( *v )[i].n_count;
      ( *v )[*node_count - 1].n = ( int * )malloc( sizeof( int ) * ( *v )[i].n_count );
      for ( j = 0; j < ( *v )[i].n_count; j++ )
      {
        diff = ( *v )[i].n[j] - res->open;
        ( *v )[*node_count - 1].n[j] = *last_node + diff + 1;
      }
    }
  }
  res->open = res->close + 1;
  res->close = *node_count - 1;
  *last_node = res->close;
}

// Duplicate a node.
void dre2_duplicate_node( struct dre2_node **v, int *node_count, int last_node, int **minimal )
{
  dre2_add_node( v, node_count, ( *v )[last_node].c, minimal, false );
  ( *v )[*node_count - 1].group_id = ( *v )[last_node].group_id;
  if ( ( *v )[last_node].c == DRE2_CHAR_CLASS )
    memcpy( ( *v )[*node_count - 1].possible, ( *v )[last_node].possible, RANGE * sizeof( int ) );
}

// Setup a character range, e.g. a{2,3}
void dre2_make_range( struct dre2_node **v, int *node_count, int *last_node, struct dre2_parse_return *res, int min, int max, int **minimal )
{
  int i, j;
  int group;
  struct dre2_node *node;
  int original;
  int node_opener;

  if ( ( *v )[*last_node].c == DRE2_GROUP_CLOSE )
  {
    group = true;
  } else
  {
    node_opener = *last_node;
    original = *last_node;
    group = false;
  }

  if ( min == 0 )
  {
    if ( ( *v )[*last_node].c != DRE2_GROUP_OPEN && ( *v )[*last_node].c != DRE2_GROUP_CLOSE )
    {
      // Duplicate the node.
      dre2_duplicate_node( v, node_count, original, minimal );
      // Set node that was duplicated to be group open.
      ( *v )[*node_count - 2].c = DRE2_GROUP_OPEN;
      node_opener = *node_count - 2;
      // Add the group close node.
      dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );
      // Add link from group open node to actual node.
      dre2_add_neighbor( v, *node_count - 3, *node_count - 2 );
      // Add link from group open node to group close node.
      dre2_add_neighbor( v, *node_count - 3, *node_count - 1 );
      // Add link from actual node to group close node.
      dre2_add_neighbor( v, *node_count - 2, *node_count - 1 );

      for ( i = *last_node; i < *node_count; i++ )
        dre2_remove_minimal( minimal, i );
      *last_node = *node_count - 1;
      original = *node_count - 2;
    } else
    {
      dre2_add_neighbor( v, res->open, res->close );
      for ( i = res->open; i <= res->close; i++ )
        dre2_remove_minimal( minimal, i );
    }
  }

  // Make the required minimum range first.
  for ( i = 0; i < min - 1; i++ )
  {
    dre2_add_neighbor( v, *last_node, *last_node + 1 );
    if ( group )
    {
      dre2_duplicate_group( v, node_count, last_node, res, minimal );
    } else
    {
      dre2_duplicate_node( v, node_count, original, minimal );
      *last_node = *node_count - 1;
      node_opener = *last_node;
    }
  }

  // If max is min, we're done.
  if ( max == min )
    return;

  if ( max == DRE2_INFINITE )
  {
    if ( group )
    {
      dre2_add_neighbor( v, res->close, res->open );
    } else
    {
      if ( min == 0 )
        dre2_add_neighbor( v, *last_node, *last_node - 1 );
      else
        dre2_add_neighbor( v, *last_node, *last_node );
    }
  } else
  {
    if ( min == 0 )
      max--;
    for ( i = min; i < max; i++ )
    {
      dre2_add_neighbor( v, *last_node, *last_node + 1 );
      if ( group )
      {
        dre2_duplicate_group( v, node_count, last_node, res, minimal );
        dre2_add_neighbor( v, res->open, res->close );
        for ( j = res->open; j <= res->close; j++ )
          dre2_remove_minimal( minimal, j );
      } else
      {
        // Duplicate the node.
        dre2_duplicate_node( v, node_count, original, minimal );
        // Add a link from the last required to here.
        dre2_add_neighbor( v, node_opener, *node_count - 1 );
        // Mark it as not minimal.
        dre2_remove_minimal( minimal, *node_count - 1 );
        // Update last node.
        *last_node = *node_count - 1;
      }
    }
    if ( !group )
    {
      dre2_add_neighbor( v, *last_node, *node_count );
      dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );
      dre2_add_neighbor( v, node_opener, *node_count - 1 );
      *last_node = *node_count - 1;
    }
  }
}

// Parsing algorithm.
struct dre2_parse_return dre2_parse_recursive( struct dre2_node **v, int *node_count, unsigned char *re, int length, int pos, int **minimal, int *group_count )
{
  int i, j, k;
  int last_node, current_group;
  int *option_end, option_count;
  int mod;
  struct dre2_parse_return ret_val, res;
  struct dre2_range_return range;
  unsigned char c;

  // Add the group open node.
  dre2_add_node( v, node_count, DRE2_GROUP_OPEN, minimal, false );

  *group_count = *group_count + 1;
  current_group = *group_count - 1;
  ( *v )[*node_count - 1].group_id = current_group;

  ret_val.open = *node_count - 1;

  // Which node was the preceeding node.
  last_node = ret_val.open;

  // End of option nodes.
  option_count = 0;
  option_end = ( int * )malloc( sizeof( int ) );

  // Loop through regex string.
  mod = false;
  while ( pos < length )
  {
    c = re[pos];
    if ( c == '(' )
    {
      res = dre2_parse_recursive( v, node_count, re, length, pos + 1, minimal, group_count );
      if ( res.pos == -1 )
      {
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }

      // Add a link from the previous node to the group open node.
      dre2_add_neighbor( v, last_node, res.open );

      // Set the regex input pos.
      pos = res.pos;

      // Update the last node.
      last_node = res.close;

      mod = true;
    } else if ( c == ')' )
    {
      if ( ret_val.open == 0 )
      {
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }

      // Add the group close node.
      dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );
      ret_val.close = *node_count - 1;
      ret_val.pos = pos;
      for ( i = 0; i < option_count; i++ )
        dre2_add_neighbor( v, option_end[i], ret_val.close );
      dre2_add_neighbor( v, last_node, ret_val.close );
      free( option_end );
      option_end = NULL;
      ( *v )[*node_count - 1].group_id = current_group;
      return ret_val;
    } else if ( c == '|' )
    {
      // Store the last node so we can setup end of group links.
      option_count++;
      option_end = ( int * )realloc( option_end, sizeof( int ) * option_count );
      option_end[option_count - 1] = last_node;

      // Reset the last node to the group open.
      last_node = ret_val.open;
      mod = false;
    } else if ( c == '[' )
    {
      // Character class.
      dre2_add_node( v, node_count, DRE2_CHAR_CLASS, minimal, false );

      // Add it to the previous node's neighbor list.
      dre2_add_neighbor( v, last_node, *node_count - 1 );

      last_node = *node_count - 1;
      pos = dre2_character_class( &( *v )[last_node], re, pos + 1 );
      if ( pos == false )
      {
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }
      mod = true;
    } else if ( c == ']' || c == '}' )
    {
      free( option_end );
      option_end = NULL;
      ret_val.pos = -1;
      return ret_val;
    } else if ( c == '\\' )
    {
      // Character class.
      dre2_add_node( v, node_count, DRE2_CHAR_CLASS, minimal, false );

      // Add it to the previous node's neighbor list.
      dre2_add_neighbor( v, last_node, *node_count - 1 );

      last_node = *node_count - 1;
      dre2_predefined_class( &( *v )[last_node], &re[pos + 1], true, false );
      pos++;
      mod = true;
    } else if ( c == '.' )
    {
      // Character class, all chars welcome.
      dre2_add_node( v, node_count, DRE2_DOT, minimal, false );

      // Add it to the previous node's neighbor list.
      dre2_add_neighbor( v, last_node, *node_count - 1 );

      last_node = *node_count - 1;
      mod = true;
    } else if ( c == '*' )
    {
      if ( mod == false )
      {
        printf( "Invalid modifier.\n" );
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }
      mod = false;
      if ( ( *v )[last_node].c == DRE2_GROUP_CLOSE )
      {
        // Add link from group open to close and vice versa.
        dre2_add_neighbor( v, res.open, res.close );
        dre2_add_neighbor( v, res.close, res.open );
        for ( i = res.open; i <= res.close; i++ )
          dre2_remove_minimal( minimal, i );
      } else
      {
        dre2_add_node( v, node_count, ( *v )[last_node].c, minimal, false );
        if ( ( *v )[last_node].c == DRE2_CHAR_CLASS )
        {
          for ( i = 0; i < RANGE; i++ )
            ( *v )[*node_count - 1].possible[i] = ( *v )[last_node].possible[i];
        }

        ( *v )[last_node].c = DRE2_GROUP_OPEN;

        dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );

        // Add a link from group open to node.
        dre2_add_neighbor( v, last_node, last_node + 1 );

        // Add a link from group open to group close.
        dre2_add_neighbor( v, last_node, *node_count - 1 );

        // Add a link from the node to itself.
        dre2_add_neighbor( v, last_node + 1, last_node + 1 );

        // Add a link from the node to the group close.
        dre2_add_neighbor( v, last_node + 1, *node_count - 1 );

        // Update the minimal bits.
        dre2_remove_minimal( minimal, last_node );
        dre2_remove_minimal( minimal, last_node + 1 );
        dre2_remove_minimal( minimal, *node_count - 1 );

        last_node = *node_count - 1;
      }
    } else if ( c == '?' )
    {
      if ( mod == false )
      {
        printf( "Invalid modifier.\n" );
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }
      mod = false;
      // If it's a group, add a link from group open to group close.
      if ( ( *v )[last_node].c == DRE2_GROUP_CLOSE )
      {
        dre2_add_neighbor( v, res.open, res.close );
        for ( i = res.open; i <= res.close; i++ )
          dre2_remove_minimal( minimal, i );
      } else
      {
        dre2_add_node( v, node_count, ( *v )[last_node].c, minimal, false );
        if ( ( *v )[last_node].c == DRE2_CHAR_CLASS )
        {
          for ( i = 0; i < RANGE; i++ )
            ( *v )[*node_count - 1].possible[i] = ( *v )[last_node].possible[i];
        }

        ( *v )[last_node].c = DRE2_GROUP_OPEN;
        dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );

        // Add a link from group open to node.
        dre2_add_neighbor( v, last_node, last_node + 1 );

        // Add a link from group open to group close.
        dre2_add_neighbor( v, last_node, *node_count - 1 );

        // Add a link from the node to the group close.
        dre2_add_neighbor( v, last_node + 1, *node_count - 1 );

        // Update the minimal bits.
        dre2_remove_minimal( minimal, last_node );
        dre2_remove_minimal( minimal, last_node + 1 );
        dre2_remove_minimal( minimal, *node_count - 1 );

        last_node = *node_count - 1;
      }
    } else if ( c == '+' )
    {
      if ( mod == false )
      {
        printf( "Invalid modifier.\n" );
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }
      mod = false;

      if ( ( *v )[last_node].c == DRE2_GROUP_CLOSE )
        dre2_add_neighbor( v, res.close, res.open );
      else
        dre2_add_neighbor( v, last_node, last_node );
    } else if ( c == '{' )
    {
      if ( mod == false )
      {
        printf( "Invalid modifier.\n" );
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }
      mod = false;

      // Get the size range.
      range = dre2_range( re, length, pos );

      // Make sure it was a valid range.
      if ( !range.valid )
      {
        free( option_end );
        option_end = NULL;
        ret_val.pos = -1;
        return ret_val;
      }

      // Setup the range.
      dre2_make_range( v, node_count, &last_node, &res, range.min, range.max, minimal );
      pos = range.pos;
    } else if ( c == '^' || c == '$' )
    {
      // Add the node.
      if ( c == '^' )
        dre2_add_node( v, node_count, DRE2_BOL, minimal, false );
      else
        dre2_add_node( v, node_count, DRE2_EOL, minimal, false );

      // Add it to the previous node's neighbor list.
      dre2_add_neighbor( v, last_node, *node_count - 1 );

      // Update last node.
      last_node = *node_count - 1;
      mod = false;
    } else
    {
      // Add the node.
      dre2_add_node( v, node_count, c, minimal, false );

      // Add it to the previous node's neighbor list.
      dre2_add_neighbor( v, last_node, *node_count - 1 );

      // Update last node.
      last_node = *node_count - 1;
      mod = true;
    }
    pos++;
  }

  if ( ret_val.open != 0 )
  {
    free( option_end );
    option_end = NULL;
    ret_val.pos = -1;
    return ret_val;
  }

  // Add links from the last node in each option group to the group close node.
  dre2_add_node( v, node_count, DRE2_GROUP_CLOSE, minimal, false );
  for ( i = 0; i < option_count; i++ )
    dre2_add_neighbor( v, option_end[i], *node_count - 1 );

  dre2_add_neighbor( v, last_node, *node_count - 1 );

  ( *v )[*node_count - 1].group_id = current_group;

  free( option_end );
  option_end = NULL;

  return ret_val;
}

// Parse function wrapper.
struct dre2 *dre2_parse( unsigned char *re, int options )
{
  int i, j;
  struct dre2_node *v, *min_v;
  int node_count, group_count;
  int length;
  int all_minimal;
  int *minimal, *new_minimal, minimal_count, *minimal_id;
  struct dre2_parse_return ret;
  struct dre2 *min_graph, *graph;
  int bol, eol, eof;

  // Setup the return graph and temp, initial graph.
  graph = ( struct dre2 * )malloc( sizeof( struct dre2 ) );
  min_graph = ( struct dre2 * )malloc( sizeof( struct dre2 ) );

  // Make sure options are set correctly.
  if ( options & DRE2_FULL_MATCH || options & DRE2_SUBMATCH )
    options = options | DRE2_GREEDY;

  // Call the recursive parse function.
  graph->options = options;
  graph->starting_points = NULL;
  graph->starting_chars = NULL;
  graph->original = NULL;
  graph->r_temp = NULL;
  graph->reachable = NULL;
  graph->state = NULL;

  v = NULL;

  minimal = ( int * )malloc( sizeof( int ) );
  node_count = 0;
  length = strlen( re );
  group_count = 0;
  ret = dre2_parse_recursive( &v, &node_count, re, length, 0, &minimal, &group_count );
  graph->group_count = group_count;
  if ( ret.pos == -1 )
  {
    cleanup_nodes( &v, node_count );
    free( minimal );
    free( v );
    minimal = NULL;
    v = NULL;
    graph->v = v;
    free( graph );
    graph = NULL;
    return graph;
  }

  graph->v = v;
  graph->count = node_count;

  dre2_add_parents( graph );

  min_graph->options = options;
  min_graph->starting_points = NULL;
  min_graph->starting_chars = ( int * )calloc( RANGE, sizeof( int ) );

  new_minimal = ( int * )calloc( graph->count, sizeof( int ) );
  minimal_id = ( int * )malloc( sizeof( int ) * graph->count );
  minimal_count = 0;

  // Strip out the group nodes and make it an epsilon-free graph.
  min_v = ( struct dre2_node * )malloc( sizeof( struct dre2 ) * graph->count );
  dre2_strip_groups( graph, min_graph, &min_v, minimal, &new_minimal, &minimal_count, &minimal_id );
  min_graph->v = min_v;

  // Setup the reverse graph.
  dre2_add_parents( min_graph );

  // Setup the skip table and find impossible chars.
  dre2_skip_table( min_graph );
  dre2_impossible_chars( min_graph );

  // Clean up the original graph's memory if we don't need it.
  if ( !( options & DRE2_SUBMATCH ) )
  {
    cleanup_dre2( graph );
    min_graph->original = NULL;
  } else
  {
    min_graph->original = graph;
  }

  // Find the best starting point and chars.
  min_graph->starting_point = dre2_starting_point( min_graph, new_minimal, minimal_id, minimal_count );
  dre2_starting_chars( min_graph, new_minimal );

  if ( min_graph->single )
  {
    for ( i = 0; i < RANGE; i++ )
    {
      if ( min_graph->starting_chars[i] )
        min_graph->c = i;
    }
  }

  if ( min_graph->starting_point == -1 )
  {
    min_graph->match_method = DRE2_MN;
  } else if ( min_graph->starting_point == 0 || min_graph->starting_point != min_graph->count - 1 )
  {
    if ( min_graph->single )
      min_graph->match_method = DRE2_SN_SC;
    else
      min_graph->match_method = DRE2_SN_MC;
  } else
  {
    if ( min_graph->single )
      min_graph->match_method = DRE2_SN_SC_H;
    else
      min_graph->match_method = DRE2_SN_MC_H;
  }

  // Make it case-insensitive.
  if ( options & DRE2_NO_CASE )
  {
    for ( i = 0; i < min_graph->count; i++ )
    {
      if ( min_graph->v[i].c == DRE2_CHAR_CLASS )
      {
        for ( j = 'a'; j <= 'z'; j++ )
        {
          if ( min_graph->v[i].possible[j] )
            min_graph->v[i].possible[j - ('a' - 'A')] = true;
        }
        for ( j = 'A'; j <= 'Z'; j++ )
        {
          if ( min_graph->v[i].possible[j] )
            min_graph->v[i].possible[j + ('a' - 'A')] = true;
        }
      }
    }
  }

  if ( options & DRE2_THREAD_SAFE )
  {
    min_graph->r_temp = NULL;
    min_graph->reachable = NULL;
    min_graph->state = NULL;
  } else
  {
    min_graph->r_temp = ( int * )malloc( sizeof( int ) * min_graph->count );
    min_graph->reachable = ( int * )malloc( sizeof( int ) * min_graph->count );
    min_graph->state = ( int * )calloc( min_graph->count, sizeof( int ) );
  }

  if ( min_graph->starting_point > 0 && min_graph->starting_point < graph->count - 1 )
  {
    if ( min_graph->match_method == DRE2_SN_SC || min_graph->match_method == DRE2_SN_MC )
      min_graph->initial_skip = dre2_initial_skip( min_graph );
  }

  min_graph->has_loop = false;
  for ( i = 0; i < min_graph->count; i++ )
  {
    for ( j = 0; j < min_graph->v[i].n_count; j++ )
    {
      if ( min_graph->v[i].n[j] <= i )
      {
        min_graph->has_loop = true;
        i = min_graph->count;
        break;
      }
    }
  }

  // Cleanup.
  free( new_minimal );
  free( minimal_id );
  free( minimal );
  new_minimal = NULL;
  minimal_id = NULL;
  minimal = NULL;

  return min_graph;
}

// Display the regex dre2.
void print_dre2( struct dre2 *graph )
{
  int i, j, k;
  int index, found;

  printf( "=======================\n" );
  printf( "|| Node || Neighbors ||\n" );
  printf( "=======================\n" );
  for ( i = 0; i < graph->count; i++ )
  {
    printf( "Node %d (%c): ", i, graph->v[i].c );
    for ( j = 0; j < graph->v[i].n_count; j++ )
      printf( "%d, ", graph->v[i].n[j] );
    printf( "\n" );

    if ( graph->v[i].c == DRE2_CHAR_CLASS )
    {
      for ( j = 0; j < RANGE; j++ )
      {
        if ( graph->v[i].possible[j] )
          printf( "x" );
        else
          printf( "." );
      }
      printf( "\n" );
    } else if ( graph->v[i].c < 0 )
    {
      if ( graph->v[i].c == DRE2_DOT )
      {
        for ( j = 0; j < RANGE; j++ )
          printf( "x" );
      } else
      {
        index = graph->v[i].c * -1 - 5;
        if ( index >= 0 && index <= 10 )
        {
          j = 0;
          for ( j = 0; j < RANGE; j++ )
          {
            k = 0;
            found = false;
            while ( dre2_predefined_classes[index][k] != -1 )
            {
              if ( dre2_predefined_classes[index][k] == j )
              {
                found = true;
                break;
              }
              k++;
            }
            if ( found )
              printf( "x" );
            else
              printf( "." );
          }
        }
      }
      printf ( "\n" );
    }
  }
  printf( "\n" );
}

// Display the reverse dre2.
void print_reverse_dre2( struct dre2 *graph )
{
  printf( "=======================\n" );
  printf( "|| Node || Parents   ||\n" );
  printf( "=======================\n" );
  int i, j;
  for ( i = graph->count - 1; i >= 0; i-- )
  {
     printf( "Node %d (%c): ", i, graph->v[i].c == DRE2_GROUP_OPEN || graph->v[i].c == DRE2_GROUP_CLOSE ? 'G' : graph->v[i].c );
     for ( j = 0; j < graph->v[i].p_count; j++ )
       printf( "%d, ", graph->v[i].p[j] );
     printf( "\n" );
  }
  printf( "\n" );
}

// Match a single node.
int dre2_char_matches( struct dre2 *graph, struct dre2_node *node, unsigned char c )
{
  if ( node->c >= 0 )
  {
    if ( c == node->c )
      return true;
    if ( graph->options & DRE2_NO_CASE )
    {
      if ( node->c >= 'a' && node->c <= 'z' && c == node->c - ( 'a' - 'A' ) )
        return true;
      else if ( node->c >= 'A' && node->c <= 'Z' && c == node->c + ( 'a' - 'A' ) )
        return true;
    }
    return false;
  }

  if ( node->c == DRE2_CHAR_CLASS )
    return node->possible[c];

  switch( node->c )
  {
    case DRE2_DOT:
      if ( c != '\0' && c != '\n' && c != '\r' )
        return true;
      return false;
    case DRE2_ALPHA:
      if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) )
        return true;
      return false;
    case DRE2_WORD:
      if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || ( c == '-' ) )
        return true;
      return false;
    case DRE2_DOMAIN:
      if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || ( c == '-' ) || ( c == '.' ) )
        return true;
      return false;
    case DRE2_URL:
      if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || ( c == '-' ) || ( c == '.' ) || ( c == '/' ) || ( c = ':' ) || ( c == '_' ) || ( c == '@' ) )
        return true;
      return false;
    case DRE2_DIGIT:
      if ( c >= '0' && c <= '9' )
        return true;
      return false;
    case DRE2_BORDER:
      if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || ( c >= '0' && c <= '9' ) || ( c == '-' ) )
        return false;
      return true;
    case DRE2_WHITE_SPACE:
      if ( c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\n' )
        return true;
      return false;
    case DRE2_SIM_DIGIT:
      if ( c >= '0' && c <= '9' )
        return true;
      if ( c == 215 || c == 225 || c == 226 || c == 231 || c == 238 || c == 239 || c == 247 || c == 250 || c == 254 )
        return true;
      return false;
    case DRE2_OBF_DIGIT:
      if ( c == 215 || c == 225 || c == 226 || c == 231 || c == 238 || c == 239 || c == 247 || c == 250 || c == 254 )
        return true;
      return false;
    case DRE2_HEX:
      if ( ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ) )
        return true;
      return false;
  }
  return false;
}

// Matcher process.
struct dre2_single_match dre2_matcher( struct dre2 *graph, unsigned char *begin_ptr, unsigned char *input, int start, int direction, int length, int *r_temp, int *reachable, int *state )
{
  int i, j, k;
  int *swapper, *next_nodes, *previous_nodes;
  int iter, l_iter;
  int matched, single_match;
  int r;
  int count, previous_count;
  int found, complete, assertion, assertion_match;
  struct dre2_node *node;
  struct dre2_single_match ret;

  ret.match = NULL;
  ret.skip_to = DRE2_INFINITE;
  ret.assertion_match = false;

  i = 0;
  next_nodes = direction == DRE2_LEFT ? graph->v[start].p : graph->v[start].n;
  count = direction == DRE2_LEFT ? graph->v[start].p_count : graph->v[start].n_count;

  if ( start == 0 || start == graph->count - 1 )
  {
    for ( i = 0; i < count; i++ )
      reachable[i] = next_nodes[i];
    l_iter = i;
  } else
  {
    reachable[0] = start;
    l_iter = 1;
  }

  assertion_match = false;
  while ( true )
  {
    // Check for valid states.
    i = 0;
    iter = 0;
    matched = false;
    complete = false;
    for ( i = 0; i < l_iter; i++ )
    {
      r = reachable[i];
      node = &graph->v[r];

      // Check if the character matches the node.
      single_match = false;
      switch ( node->c )
      {
        case DRE2_BOL:
        case DRE2_EOF:
        case DRE2_EOL:
          assertion = true;
          break;
        default:
          assertion = false;
          break;
      }

      if ( node->c == DRE2_BOL )
      {
        if ( ( direction == DRE2_LEFT && input - begin_ptr == -1 ) || ( direction == DRE2_RIGHT && input - begin_ptr == 0 ) )
          single_match = true;
      } else if ( node->c == DRE2_EOL && ( *input == '\n' || *input == '\0' ) )
      {
        single_match = true;
      } else if ( node->c == DRE2_EOF && *input == '\0' )
      {
        single_match = true;
      } else if ( node->c == DRE2_EOF && *input == '\n' && input - begin_ptr + 1 == length )
      {
        single_match = true;
      } else if ( node->c == DRE2_EOF && *input == ' ' && input - begin_ptr + 1 == length - 1 )
      {
        single_match = true;
      } else if ( dre2_char_matches( graph, node, *input ) )
      {
        single_match = true;
      }

      if ( assertion && single_match )
        assertion_match = true;

      // Set the next possible nodes.
      if ( single_match == true )
      {
        matched = true;

        // Set the next state to include this node's neighbors/parents.
        next_nodes = direction == DRE2_LEFT ? node->p : node->n;
        count = direction == DRE2_LEFT ? node->p_count : node->n_count;
        for ( j = 0; j < count; j++ )
        {
          if ( !state[next_nodes[j]] )
          {
            state[next_nodes[j]] = true;
            r_temp[iter++] = next_nodes[j];
            if ( ( direction == DRE2_RIGHT && next_nodes[j] == graph->count - 1 ) || ( direction == DRE2_LEFT && next_nodes[j] == 0 ) )
              complete = true;
          }
        }
      } else if ( graph->impossible[*input] )
      {
        ret.skip_to = input - begin_ptr;
      }
    }

    if ( !matched && graph->impossible[*input] )
    {
      for ( i = 0; i < graph->v[0].n_count; i++ )
      {
        if ( direction == DRE2_LEFT && graph->v[graph->v[0].n[i]].c == DRE2_BOL )
        {
          ret.skip_to = length;
          break;
        }
      }
    }

    if ( complete )
    {
      ret.match = input;
      ret.assertion_match = assertion_match;
      if ( !( graph->options & DRE2_GREEDY ) )
      {
        for ( i = 0; i < iter; i++ )
          state[r_temp[i]] = false;
        return ret;
      }
    }

    // Reset the state lookup table.
    for ( i = 0; i < iter; i++ )
      state[r_temp[i]] = false;

    l_iter = iter;

    swapper = reachable;
    reachable = r_temp;
    r_temp = swapper;

    // Increment/Decrement input.
    if ( !assertion_match )
    {
      if ( direction == DRE2_LEFT )
        *input--;
      else
        *input++;
    }

    // If none of the active states matched, the regex failed to match.
    if ( matched == false )
      return ret;
  }
  return ret;
}

// Extract the matching portion of the regex.
void dre2_matched_substring( unsigned char *input, struct dre2_match_value *value, unsigned char **match )
{
  int size;

  if ( value->start_pos < 0 )
    value->start_pos = 0;
  size = value->end_pos - value->start_pos;
  if ( size <= 0 )
  {
    ( *match )[0] = '\0';
  } else
  {
    sprintf( *match, "%.*s", size, input + value->start_pos );
  }
}


// Match when there is a single character and single node, horspool.
struct dre2_match_value dre2_sn_sc_horspool( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  int i;
  unsigned char c, *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  result.assertion_match = false;
  c = graph->c;
  if ( graph->min_length > 0 )
    pch = memchr( input + graph->min_length - 1, c, length - graph->min_length + 1 );
  else
    pch = input;

  while ( pch != NULL && pch - input <= length && *pch != '\0' )
  {
    result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_LEFT, length, r_temp, reachable, state );
    if ( result.match != NULL )
    {
      ret_val.can_continue = graph->has_loop;
      ret_val.matched = true;
      ret_val.start_pos = result.match - input;
      ret_val.end_pos = pch - input + 1;
      return ret_val;
    }
    if ( result.assertion_match )
      pch = input + length;

    pch = memchr( pch + graph->skip_table[*pch], c, length - ( pch - input ) );
  }
  ret_val.matched = false;
  return ret_val;
}

// Match when there is a single character and single node.
struct dre2_match_value dre2_sn_sc( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  unsigned char c, *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  result.assertion_match = false;
  c = graph->c;
  pch = memchr( input + graph->initial_skip, c, length );
  while ( pch != NULL && pch - input <= length && *pch != '\0' )
  {
    if ( graph->starting_point == 0 )
    {
      result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_RIGHT, length, r_temp, reachable, state );
      if ( result.match != NULL )
      {
        ret_val.matched = true;
        ret_val.start_pos = pch - input;
        ret_val.end_pos = result.match - input + 1;
        return ret_val;
      }
      if ( result.skip_to != DRE2_INFINITE )
        pch = input + result.skip_to;
    } else
    {
      result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_LEFT, length, r_temp, reachable, state );
      if ( result.match != NULL )
      {
        ret_val.start_pos = result.match - input;
        result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_RIGHT, length, r_temp, reachable, state );
        if ( result.match != NULL )
        {
          ret_val.matched = true;
          ret_val.end_pos = result.match - input + 1;
          return ret_val;
        }
        if ( result.skip_to != DRE2_INFINITE )
          pch = input + result.skip_to;
      }
      if ( result.assertion_match )
          pch = input + length;
    }
    pch = memchr( pch + 1, c, length - ( pch - input ) );
  }
  ret_val.matched = false;
  return ret_val;
}

// Match when there is a single node but multiple characters, horspool.
struct dre2_match_value dre2_sn_mc_horspool( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  unsigned char *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  result.assertion_match = false;
  if ( graph->min_length > 0 )
    pch = input + graph->min_length - 1;
  else
    pch = input;
  while ( pch - input <= length && *pch != '\0' && !graph->starting_chars[*pch] )
    *pch++;
  while ( pch - input <= length && *pch != '\0' )
  {
    result = dre2_matcher( graph, input, pch, graph->count - 1, DRE2_LEFT, length, r_temp, reachable, state );
    if ( result.match != NULL )
    {
      ret_val.matched = true;
      ret_val.start_pos = result.match - input;
      ret_val.end_pos = pch - input + 1;
      return ret_val;
    }
    if ( result.assertion_match )
      pch = input + length;

    pch = pch + graph->skip_table[*pch];
    while ( pch - input <= length && *pch != '\0' && !graph->starting_chars[*pch] )
      *pch++;
  }
  ret_val.matched = false;
  return ret_val;
}

// Match when there is a single node but multiple characters.
struct dre2_match_value dre2_sn_mc( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  unsigned char *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;
  int assertion_match;

  assertion_match = false;
  result.assertion_match = false;

  pch = input + graph->initial_skip;
  while ( pch - input <= length && *pch != '\0' && !graph->starting_chars[*pch] )
    *pch++;
  while ( pch - input <= length && *pch != '\0' )
  {
    if ( graph->starting_point == 0 )
    {
      result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_RIGHT, length, r_temp, reachable, state );
      if ( result.match != NULL )
      {
        ret_val.matched = true;
        ret_val.start_pos = pch - input;
        ret_val.end_pos = result.match - input + 1;
        return ret_val;
      }
      if ( result.skip_to != DRE2_INFINITE )
        pch = input + result.skip_to;
    } else
    {
      result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_LEFT, length, r_temp, reachable, state );
      if ( result.match != NULL )
      {
        assertion_match = result.assertion_match;
        ret_val.start_pos = result.match - input;
        result = dre2_matcher( graph, input, pch, graph->starting_point, DRE2_RIGHT, length, r_temp, reachable, state );
        if ( result.match != NULL )
        {
          ret_val.matched = true;
          ret_val.end_pos = result.match - input + 1;
          return ret_val;
        }
        if ( assertion_match )
          pch = input + length;
        else if( result.skip_to != DRE2_INFINITE )
          pch = input + result.skip_to;
      }
      if ( result.assertion_match )
        pch = input + length;
      if ( result.skip_to != DRE2_INFINITE )
        pch = input + result.skip_to;
    }
    *pch++;
    while ( pch - input <= length && *pch != 0 && !graph->starting_chars[*pch] )
      *pch++;
  }
  ret_val.matched = false;
  return ret_val;
}

// Match when there are multiple nodes.
struct dre2_match_value dre2_mn( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  int i;
  unsigned char *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  result.assertion_match = false;
  pch = input;
  while ( pch - input <= length && *pch != '\0' && !graph->starting_chars[*pch] )
    *pch++;
  while ( pch - input <= length && *pch != '\0' )
  {
    for ( i = 0; i < graph->starting_count; i++ )
    {
      result = dre2_matcher( graph, input, pch, graph->starting_points[i], DRE2_LEFT, length, r_temp, reachable, state );
      if ( result.match != NULL )
      {
        ret_val.start_pos = result.match - input;
        result = dre2_matcher( graph, input, pch, graph->starting_points[i], DRE2_RIGHT, length, r_temp, reachable, state );
        if ( result.match != NULL )
        {
          ret_val.matched = true;
          ret_val.end_pos = result.match - input + 1; 
          return ret_val;
        }
        if ( result.skip_to != DRE2_INFINITE )
          pch = input + result.skip_to;
      }
      if ( result.assertion_match )
        pch = input + length;
    }
    *pch++;
    while ( pch - input <= length && *pch != 0 && !graph->starting_chars[*pch] )
      *pch++;
  }
  ret_val.matched = false;
  return ret_val;
}

// Check if the string is a complete match.
struct dre2_match_value dre2_full_match( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state )
{
  unsigned char *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  result.assertion_match = false;
  ret_val.start_pos = 0;
  ret_val.end_pos = length;
  ret_val.matched = false;
  pch = input;
  result = dre2_matcher( graph, input, pch, 0, DRE2_RIGHT, length, r_temp, reachable, state );
  if ( result.match != NULL )
  {
    if ( result.match - input == length || result.match - input == length + 1 )
      ret_val.matched = true;
    if ( result.match - input == length - 1 && ( input[length - 1] == '\n' || input[length - 1] == '\r' ) )
      ret_val.matched = true;
    if ( result.match - input == length - 2 && ( input[length - 2] == '\r' && input[length - 1] == '\n' ) )
      ret_val.matched = true;
  }
  return ret_val;
}

// Expand the original match for greedy mode.
struct dre2_match_value dre2_expanded_match( struct dre2 *graph, unsigned char *input, int length, int *r_temp, int *reachable, int *state, struct dre2_match_value *original_match )
{
  unsigned char *pch;
  struct dre2_single_match result;
  struct dre2_match_value ret_val;

  ret_val.start_pos = original_match->start_pos;
  ret_val.matched = true;
  pch = input + original_match->start_pos;
  result = dre2_matcher( graph, input + original_match->start_pos, pch, 0, DRE2_RIGHT, length, r_temp, reachable, state );
  if ( result.match != NULL )
    ret_val.end_pos = result.match - input + 1;
  return ret_val;
}

// Regex match driver.
struct dre2_match_value dre2_match( struct dre2 *graph, unsigned char *input )
{
  int i, length;
  struct dre2_match_value result;
  int *r_temp, *reachable, *state;

  result.matched = false;

  // Make sure the string is even long enough before attempting matching.
  length = strlen( input );

  if ( length < graph->min_length )
    return result;

  if ( graph->options & DRE2_THREAD_SAFE )
  {
    r_temp = ( int * )malloc( sizeof( int ) * graph->count );
    reachable = ( int * )malloc( sizeof( int ) * graph->count );
    state = ( int * )calloc( graph->count, sizeof( int ) );
  } else
  {
    r_temp = graph->r_temp;
    reachable = graph->reachable;
    state = graph->state;
  }

  if ( graph->options & DRE2_FULL_MATCH )
  {
    result = dre2_full_match( graph, input, length, r_temp, reachable, state );
  } else
  {
    switch ( graph->match_method )
    {
      case DRE2_SN_SC_H:
        result = dre2_sn_sc_horspool( graph, input, length, r_temp, reachable, state );
        break;
      case DRE2_SN_SC:
        result = dre2_sn_sc( graph, input, length, r_temp, reachable, state );
        break;
      case DRE2_SN_MC_H:
        result = dre2_sn_mc_horspool( graph, input, length, r_temp, reachable, state );
        break;
      case DRE2_SN_MC:
        result = dre2_sn_mc( graph, input, length, r_temp, reachable, state );
        break;
      case DRE2_MN:
        result = dre2_mn( graph, input, length, r_temp, reachable, state );
        break;
    }
  }

  if ( result.matched && ( graph->options & DRE2_GREEDY ) && graph->has_loop )
    result = dre2_expanded_match( graph, input, length, r_temp, reachable, state, &result );

  if ( ( graph->options & DRE2_THREAD_SAFE ) || graph->count >= RANGE )
  {
    free( reachable ); reachable = NULL;
    free( r_temp ); r_temp = NULL;
    free( state ); state = NULL;
  }
  return result;
}

// Recursive backtracking function - also sets group open/close positions.
int dre2_backtrack_recursive( struct dre2 *graph, unsigned char *input, int pos, int id, int **state, int **group_open, int **group_close )
{
  int i, j;
  int offset;
  int g_open, g_close;
  unsigned char *tp;
  int *last_state;
  int assertion, single_match;
  struct dre2_node *node;
  int length = strlen( input );

  tp = input + pos;

  // If we are at the regex close node, then we've matched as much as possible, return.
  if ( id == graph->count - 1 )
    return true;

  // If we are past the end of input, we can't match, return false.
  if ( *tp == '\0' && ( graph->v[id].c != DRE2_GROUP_OPEN && graph->v[id].c != DRE2_GROUP_CLOSE ) &&
         ( graph->v[id].c != DRE2_EOF && graph->v[id].c != DRE2_EOL && graph->v[id].c != DRE2_BOL ) )
    return false;

  // Make sure we haven't already tried this node.
  if ( ( *state )[id] )
    return false;

  last_state = ( int * )malloc( sizeof( int ) * graph->count );
  for ( i = 0; i < graph->count; i++ )
    last_state[i] = ( *state )[i];

  ( *state )[id] = true;

  // Match the input character if it's not a group.
  if ( graph->v[id].c != DRE2_GROUP_OPEN && graph->v[id].c != DRE2_GROUP_CLOSE )
  {
    single_match = false;
    node = &graph->v[id];
    switch ( node->c )
    {
      case DRE2_BOL:
      case DRE2_EOF:
      case DRE2_EOL:
        assertion = true;
        break;
      default:
        assertion = false;
        break;
    }

    if ( node->c == DRE2_BOL && pos == 0 )
    {
      single_match = true;
    } else if ( node->c == DRE2_EOL && ( *tp == '\n' || *tp == '\0' ) )
    {
      single_match = true;
    } else if ( node->c == DRE2_EOF && *tp == '\0' )
    {
      single_match = true;
    } else if ( node->c == DRE2_EOF && *tp == '\n' && tp - input + 1 == length )
    {
      single_match = true;
    } else if ( node->c == DRE2_EOF && *tp == ' ' && tp - input + 1 == length - 1 )
    {
      single_match = true;
    } else if ( dre2_char_matches( graph, node, *tp ) )
    {
      single_match = true;
    }

    if ( single_match )
    {
      if ( !assertion )
      {
        offset = 1;
        pos++;
      }
      for ( i = 0; i < graph->count; i++ )
        ( *state )[i] = false;
    } else
    {
      free( last_state );
      last_state = NULL;
      return false;
    }
  } else
  {
    offset = 0;
  }

  // Set the group open and close positions, but also track where it was so we can revert later if needed.
  if ( graph->v[id].c == DRE2_GROUP_OPEN && graph->v[id].group_id > 0 )
  {
    g_open = ( *group_open )[graph->v[id].group_id - 1];
    ( *group_open )[graph->v[id].group_id - 1] = pos;
  } else if ( graph->v[id].c == DRE2_GROUP_CLOSE && graph->v[id].group_id > 0 )
  {
    g_close = ( *group_close )[graph->v[id].group_id - 1];
    ( *group_close )[graph->v[id].group_id - 1] = pos;
  }

  // Check each of this nodes neighbors.
  for ( i = 0; i < graph->v[id].n_count; i++ )
  {
    // If the recursive function returns true, the regex matched.
    if ( dre2_backtrack_recursive( graph, input, pos, graph->v[id].n[i], state, group_open, group_close ) )
    {
      free( last_state );
      last_state = NULL;
      return true;
    }
  }

  // Revert state table on failure as well.
  for ( i = 0; i < graph->count; i++ )
    ( *state )[i] = last_state[i]; //false;

  // Revert group open/close on failure.
  if ( graph->v[id].c == DRE2_GROUP_OPEN && graph->v[id].group_id > 0 )
  {
    ( *group_open )[graph->v[id].group_id - 1] = g_open;
  } else if ( graph->v[id].c == DRE2_GROUP_CLOSE && graph->v[id].group_id > 0 )
  {
    ( *group_close )[graph->v[id].group_id - 1] = g_close;
  }
  free( last_state );
  last_state = NULL;
  return false;
}

// Perform backtracking match, returning submatch info (if any)
void dre2_backtrack_match( struct dre2 *graph, unsigned char *input, unsigned char ***submatches )
{
  int i, j;
  int matched, pos;
  int *state;
  int *group_open, *group_close;

  // Allocate some memory for the state table to ensure we don't ever get in an infinite loop.
  state = ( int * )calloc( graph->original->count, sizeof( int ) );

  // Allocate some memory for extracting submatches.
  if ( graph->original->group_count > 1 )
  {
    group_open = ( int * )calloc( graph->original->group_count, sizeof( int ) );
    group_close = ( int * )calloc( graph->original->group_count, sizeof( int ) );
  } else
  {
    return;
  }

  if ( ( matched = dre2_backtrack_recursive( graph->original, input, 0, 0, &state, &group_open, &group_close ) ) )
  {
    for ( i = 1; i < graph->original->group_count; i++ )
    {
      if ( group_close[i - 1] > group_open[i - 1] )
        sprintf( ( *submatches )[i - 1], "%.*s", group_close[i - 1] - group_open[i - 1], input + group_open[i - 1] );
      else
        ( *submatches )[i - 1][0] = '\0';
    }
  } else
  {
    printf( "FAIL!\n" );
  }

  // Free up memory used.
  if ( graph->original->group_count > 1 )
  {
    free( state ); state = NULL;
    free( group_open ); group_open = NULL;
    free( group_close ); group_close = NULL;
  }
}

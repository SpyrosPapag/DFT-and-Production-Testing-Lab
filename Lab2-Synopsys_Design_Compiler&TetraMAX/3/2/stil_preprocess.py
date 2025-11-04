import re

def parse_stil_to_vec(stil_path, vec_path):
    # Read entire file
    with open(stil_path, 'r') as f:
        content = f.read()

    # Split out pattern blocks, keeping the header
    blocks = re.split(r'(?="pattern\s+\d+\")', content)

    patterns = []
    for blk in blocks:
        blk = blk.strip()
        if not blk.startswith('"pattern'):
            continue

        # Get the pattern index for ordering
        m_id = re.match(r'"pattern\s+(\d+)\"', blk)
        pat_id = int(m_id.group(1)) if m_id else None

        # Grab test_si (scan_in)
        m_si = re.search(r'"test_si"\s*=\s*([01]+);', blk)
        scan_in = m_si.group(1) if m_si else ''

        # Grab all test_so occurrences in the block
        sos = re.findall(r'"test_so"\s*=\s*([HL01]+);', blk)

        # Grab primary inputs (_pi), allow 0,1,P
        m_pi = re.search(r'"_pi"\s*=\s*([01P]+);', blk)
        primary_in = m_pi.group(1) if m_pi else ''

        # Grab primary outputs (_po), allow H,L,0,1,X
        m_po = re.search(r'"_po"\s*=\s*([HL01X]+);', blk)
        primary_out = m_po.group(1) if m_po else ''

        patterns.append({
            'id':      pat_id,
            'scan_in': scan_in,
            'sos':     sos,
            'pi':      primary_in,
            'po':      primary_out
        })

    # Sort by pattern index
    patterns.sort(key=lambda x: x['id'] if x['id'] is not None else 0)

    with open(vec_path, 'w') as vf:
        n = len(patterns)
        for i, entry in enumerate(patterns):
            pi = patterns[i]['pi'].replace('P','1')
                
            final_so = entry['sos'][0].replace('H', '1').replace('L', '0') if entry['sos'] else 'X' * 179
            final_po = entry['po'].replace('H', '1').replace('L', '0') if entry['po'] else ''

            if pi and entry['scan_in'] and final_po and final_so:
                vf.write(f"{pi[0]} {pi[-2]} {pi[-1]} {pi[1:-2]} {entry['scan_in']} {final_po[:-1]} {final_so}\n")
            if i==283: 
                vf.write(f"{'X'} {'X'} {'X'} {'X' * 35} {'X' * 179} {'X' * 49} {entry['sos'][1].replace('H', '1').replace('L', '0')}\n")


parse_stil_to_vec("s5378_myvectors.stil", "my_s5378.vec")